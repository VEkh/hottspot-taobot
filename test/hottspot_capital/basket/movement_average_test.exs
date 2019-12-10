defmodule HottspotCapital.Basket.Movement.AverageTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Basket.Movement.Average, as: Movement
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.StockQuoteStubs

  describe ".calculate" do
    test "returns relative movement of reference stock to its basket" do
      ["HOTT", "MSFT", "AMZN", "GOOG", "FB", "APPL"]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {symbol, data} ->
        Factory.create_company(%{symbol: symbol})

        data
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({2019, 03, 12 - index}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      assert %Movement{
               basket_movement: -0.316258,
               reference: %{
                 last_two_closes: [
                   %{"close" => 372.06},
                   %{"close" => 933.57}
                 ],
                 movement: -0.601465,
                 symbol: "HOTT"
               }
             } = Movement.calculate("HOTT", date_limit: ~D[2019-03-12])
    end
  end

  defp stubbed_closes_and_volumes do
    # close        volume
    ~w[
      3.7206e+02   2.6224e+05
      9.3357e+02   6.3718e+05
      6.5232e+02   4.8821e+05

      2.3723e+02   4.9149e+05
      3.0500e+02   1.3373e+04
      8.4866e+02   1.1450e+05

      8.3617e+02   2.3985e+05
      8.0350e+02   7.5613e+05
      1.3247e+01   5.7128e+05

      9.8741e+02   3.2806e+05
      7.8717e+02   1.1994e+05
      1.0268e+02   1.7471e+04

      2.1186e+02   1.2202e+05
      9.4379e+02   9.2037e+05
      9.3438e+02   1.4152e+05

      3.0376e+02   6.5843e+05
      9.2867e+02   6.0538e+04
      4.9273e+01   3.8233e+05
    ]
    |> StockQuoteStubs.group_closes_and_volumes(days: 3)
  end
end
