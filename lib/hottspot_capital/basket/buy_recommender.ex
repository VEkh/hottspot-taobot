defmodule HottspotCapital.Basket.BuyRecommender do
  alias HottspotCapital.Basket.Movement
  alias HottspotCapital.Company
  alias HottspotCapital.Repo

  @max_concurrency Repo.config() |> Keyword.get(:pool_size)

  def recommend(options \\ []) do
    %{date_limit: date_limit} = merged_options = merge_options(options)

    Company.get_largest(200)
    |> Task.async_stream(
      fn %{symbol: symbol} ->
        log("Calculating movement for: #{symbol}", merged_options)
        Movement.calculate(symbol, date_limit: date_limit)
      end,
      max_concurrency: @max_concurrency,
      timeout: :infinity
    )
    |> Enum.map(&Kernel.elem(&1, 1))
    |> apply_buy_filter()
    |> Enum.sort(fn a, b ->
      [a_last_close, b_last_close] =
        [a, b]
        |> Enum.map(fn movement ->
          get_in(
            movement,
            [:reference, :last_two_closes, Access.at(0), "close"]
          )
        end)

      a_last_close <= b_last_close
    end)
    |> respond(merged_options)
  end

  defp apply_buy_filter(movements) do
    movements
    |> Enum.filter(fn
      %Movement{
        basket_movement: basket_movement,
        reference: %{movement: reference_movement}
      } ->
        # .0.5704697986577181 (weighted average basket movement)
        # basket_movement >= 0.1 && reference_movement <= 0

        # 0.6568933250155957 (wrong sum basket movement)
        # basket_movement >= 0.005 && reference_movement <= 0

        # Lenny Production
        # Average                     => Total Accuracy: 0.5107604017216643
        # Movement (Weighted Average) => Total Accuracy: 0.544014904517932
        # Sum                         => Total Accuracy: 0.569060773480663
        # Sum (Inverted)              => Total Accuracy: 0.5236348818255909
        # Vector Magnitude            => Total Accuracy: 0.5503931379556827
        # basket_movement >= 0.005 && reference_movement <= 0

        # Lenny Production Vector Magnitude (50 tests)
        # Trial 1 => Total Accuracy: 0.6808510638297872
        # Trial 2 => Total Accuracy: 0.6578947368421053

        # Lenny Production Vector Magnitude (100 tests)
        # Trial 1 => Total Accuracy: 0.49019607843137253
        # basket_movement > 0.02 && reference_movement <= 0

        # TODO: Go backwards. On the days where a stock's price increased from
        # one day to the next, what did it's basket do?
        # Lenny Production Vector Magnitude (100 tests)
        # Trial 1 => Total Accuracy: 0.34210526315789475
        basket_movement > 0.03 && reference_movement <= 0

      _ ->
        false
    end)
  end

  defp log(message, %{verbose: true}), do: IO.puts(message)
  defp log(_message, _), do: nil

  defp merge_options(options) do
    defaults = [
      date_limit: Date.utc_today(),
      format: :movement,
      verbose: Mix.env() == :dev
    ]

    defaults
    |> Keyword.merge(options)
    |> Enum.into(%{})
  end

  defp respond(movements, %{format: :symbol}) do
    movements
    |> Enum.map(fn movement ->
      get_in(movement, [:reference, :symbol])
    end)
  end

  defp respond(movements, _), do: movements
end
