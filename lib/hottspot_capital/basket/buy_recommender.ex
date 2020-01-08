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
    |> Enum.sort(&sort_by_basket_movement/2)
    |> respond(merged_options)
  end

  defp apply_buy_filter(movements) do
    movements
    |> Enum.filter(fn
      %Movement{
        basket_movement: basket_movement,
        reference: %{movement: reference_movement}
      } ->
        basket_movement > 0 &&
          basket_movement < 0.5 &&
          basket_movement - reference_movement > 0.001

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

  defp sort_by_basket_movement(a, b) do
    [a, b] =
      [a, b]
      |> Enum.map(fn %{basket_movement: basket_movement} ->
        basket_movement
      end)

    b <= a
  end
end
