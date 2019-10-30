defmodule HottspotCapital.Basket.BuyRecommender do
  alias HottspotCapital.Basket.Movement
  alias HottspotCapital.Company

  def recommend(options \\ []) do
    merged_options = merge_options(options)

    Company.get_largest(200)
    |> Task.async_stream(fn %{symbol: symbol} ->
      log("Calculating movement for: #{symbol}", merged_options)
      Movement.calculate(symbol)
    end)
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
    |> Enum.filter(fn movement ->
      %Movement{
        basket_movement: basket_movement,
        reference: %{movement: reference_movement}
      } = movement

      basket_movement >= 0.1 && reference_movement <= 0
    end)
  end

  defp log(message, %{verbose: true}), do: IO.puts(message)
  defp log(_message, _), do: nil

  defp merge_options(options) do
    defaults = [
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
