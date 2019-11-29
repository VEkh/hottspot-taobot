defmodule HottspotCapital.Basket.BuyRecommender.BackTester do
  require Ecto.Query

  use Agent

  alias HottspotCapital.Basket.BuyRecommender
  alias HottspotCapital.Repo
  alias HottspotCapital.SQLQueryParser
  alias HottspotCapital.StockQuote

  defdelegate get_and_update(map, key, fun), to: Map

  defstruct accuracy: %{correct: [], incorrect: []},
            dates: [],
            excluded_dates: [],
            test_count: 0,
            tested_dates: [],
            tests_run: 0

  def backtest(test_count) do
    init(test_count)
    test_dates()

    get_state()
    |> Map.get(:accuracy)
    |> calculate_accuracy()
    |> log_total_accuracy(env: Mix.env())
  end

  defp calculate_accuracy(%{correct: [], incorrect: []}),
    do: "Inconclusive -- No (in)correct recommendations."

  defp calculate_accuracy(%{correct: correct, incorrect: incorrect}) do
    correct_count = length(correct)
    correct_count / (correct_count + length(incorrect))
  end

  defp calculate_movement(date: date, symbol: symbol) do
    {query, params} =
      """
      SELECT
        from_date_stock_quotes.symbol,
        from_date_stock_quotes.close AS from,
        to_date_stock_quotes.close AS to
      FROM (
        SELECT close, symbol FROM stock_quotes
        WHERE symbol = $symbol AND date = $date
      ) from_date_stock_quotes
      JOIN (
        SELECT close, date, symbol FROM stock_quotes
        WHERE date > $date
      ) to_date_stock_quotes
        ON to_date_stock_quotes.symbol = from_date_stock_quotes.symbol
      ORDER BY to_date_stock_quotes.date ASC
      LIMIT 1
      ;
      """
      |> SQLQueryParser.named_to_ordered_params(
        date: date,
        symbol: symbol
      )

    [[^symbol, from, to]] =
      query
      |> Repo.query!(params)
      |> Map.get(:rows)

    [from, to]
  end

  defp calculate_date_accuracy([], _options), do: nil

  defp calculate_date_accuracy(symbols, date: date) do
    symbols
    |> Enum.reduce(%{correct: [], incorrect: []}, fn symbol, acc ->
      [from, to] = calculate_movement(date: date, symbol: symbol)

      key =
        if to > from do
          :correct
        else
          :incorrect
        end

      update_accuracy(key: key, symbol: symbol)
      update_in(acc, [key], fn list -> list ++ [symbol] end)
    end)
    |> log_date_accuracy(env: Mix.env())
  end

  defp get_state(), do: Agent.get(__MODULE__, fn state -> state end)

  defp log_date_accuracy(_results, env: :test), do: nil

  defp log_date_accuracy(results, env: _env) do
    accuracy = calculate_accuracy(results)

    [:yellow, "Accuracy: #{accuracy}\n"]
    |> IO.ANSI.format()
    |> IO.puts()
  end

  defp log_total_accuracy(accuracy, env: :test), do: accuracy

  defp log_total_accuracy(accuracy, env: _) do
    [:green, "Total Accuracy: #{accuracy}\n"]
    |> IO.ANSI.format()
    |> IO.puts()

    accuracy
  end

  defp increment_test_counter() do
    Agent.update(__MODULE__, fn %{tests_run: tests_run} = state ->
      Map.put(state, :tests_run, tests_run + 1)
    end)
  end

  defp init(test_count) do
    init_state =
      %__MODULE__{test_count: test_count}
      |> put_dates()

    start_status = Agent.start_link(fn -> init_state end, name: __MODULE__)

    case start_status do
      {:error, {:already_started, _pid}} ->
        Agent.update(__MODULE__, fn _ -> init_state end)

      result ->
        result
    end
  end

  defp log_test(date: _, env: :test), do: nil

  defp log_test(date: date, env: _env) do
    increment_test_counter()

    %{
      tests_run: tests_run,
      test_count: test_count
    } = get_state()

    [:cyan, "Test #{tests_run} of #{test_count}:"]
    |> IO.ANSI.format()
    |> IO.puts()

    IO.puts("Testing recommender accuracy for: #{Date.to_string(date)}")
  end

  defp put_dates(context) do
    dates =
      Ecto.Query.from(
        stock_quotes in StockQuote,
        distinct: [stock_quotes.date],
        order_by: [asc: stock_quotes.date],
        select: stock_quotes.date
      )
      |> Repo.all()

    excluded_dates = Enum.take(dates, 2) ++ Enum.take(dates, -1)

    %{context | dates: dates, excluded_dates: excluded_dates}
  end

  defp test_date(date) do
    log_test(date: date, env: Mix.env())

    [
      date_limit: date,
      format: :symbol,
      verbose: false
    ]
    |> BuyRecommender.recommend()
    |> calculate_date_accuracy(date: date)
  end

  defp test_dates() do
    %{
      dates: dates,
      excluded_dates: excluded_dates,
      test_count: test_count
    } = get_state()

    dates
    |> Enum.filter(fn date -> date not in excluded_dates end)
    |> Enum.shuffle()
    |> Enum.take(test_count)
    |> Enum.each(&test_date/1)
  end

  defp update_accuracy(key: key, symbol: symbol) do
    Agent.update(
      __MODULE__,
      fn state ->
        update_in(state, [:accuracy, key], fn list ->
          list ++ [symbol]
        end)
      end
    )
  end
end
