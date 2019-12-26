defmodule HottspotCapital.Test.Mocks.IexApiClient do
  alias HottspotCapital.Test.Mocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  def get("/ref-data/symbols") do
    mocked_symbols =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_symbols
      ])

    case mocked_symbols do
      nil -> IexApiStubs.symbols()
      symbols -> symbols
    end
  end

  def get("/stock/" <> rest) do
    case String.split(rest, "/") do
      [_symbol, "chart", range] -> get_historical_stock_quotes(range)
      [_symbol, "stats", "beta"] -> get_stock_beta()
      [symbol, "company"] -> get_company(symbol)
      [symbol, "quote" <> _ | _] -> get_stock_quote(symbol)
    end
  end

  def get_historical_stock_quotes(range) do
    %{"date" => previous_date} = previous_stock_quote = IexApiStubs.historical_stock_quote()

    [_, year_range, "y"] = Regex.run(~r/(\d+)(\w)/, range)

    {previous_year, previous_month, previous_day} =
      previous_date
      |> Date.from_iso8601!()
      |> Date.to_erl()

    earliest_year = previous_year - String.to_integer(year_range)

    earliest_year..previous_year
    |> Enum.map(fn year ->
      date =
        {year, previous_month, previous_day}
        |> Date.from_erl!()
        |> Date.to_iso8601()

      Map.put(previous_stock_quote, "date", date)
    end)
  end

  defp get_company(symbol) do
    mocked_company =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_company
      ])

    case mocked_company do
      nil -> IexApiStubs.company(symbol)
      company -> company
    end
  end

  defp get_stock_quote(symbol) do
    mocked_stock =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_stock
      ])

    case mocked_stock do
      nil -> IexApiStubs.stock_quote(symbol)
      stock -> stock
    end
  end

  defp get_stock_beta() do
    mocked_volatility =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_stock_beta
      ])

    case mocked_volatility do
      nil -> -0.66666
      volatility -> volatility
    end
  end
end
