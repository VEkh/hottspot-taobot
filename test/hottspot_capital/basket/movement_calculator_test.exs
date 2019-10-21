defmodule HottspotCapital.Basket.MovementCalculatorTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Basket.MovementCalculator
  alias HottspotCapital.Test.Factory

  describe ".calculate" do
    test "returns relative movement of reference stock to its basket" do
      ["HOTT", "MSFT", "AMZN", "GOOG", "FB", "APPL"]
      |> Enum.zip(stubbed_stock_quotes())
      |> Enum.each(fn {symbol, data} ->
        Factory.create_company(%{symbol: symbol})

        data
        |> Enum.chunk_every(2)
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({2019, 08, 26 - index}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      assert %{
               "basket_movement" => -0.459617,
               "reference" => %{
                 "last_two_closes" => [
                   %{"close" => 372.06},
                   %{"close" => 933.57}
                 ],
                 "movement" => -0.601465,
                 "symbol" => "HOTT"
               }
             } = MovementCalculator.calculate("HOTT")
    end

    test "accepts date_limit" do
      date_limit = ~D[2016-08-27]

      [
        %{symbol: "HOTT", is_within_date_limit: true},
        %{symbol: "MSFT", is_within_date_limit: false},
        %{symbol: "AMZN", is_within_date_limit: true},
        %{symbol: "GOOG", is_within_date_limit: false},
        %{symbol: "FB", is_within_date_limit: true},
        %{symbol: "APPL", is_within_date_limit: false}
      ]
      |> Enum.zip(stubbed_stock_quotes())
      |> Enum.each(fn {
                        %{is_within_date_limit: is_within_date_limit, symbol: symbol},
                        data
                      } ->
        Factory.create_company(%{symbol: symbol})

        data
        |> Enum.chunk_every(2)
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          dates =
            case [symbol, is_within_date_limit] do
              ["HOTT", _] ->
                [
                  Date.from_erl!({2016, 08, 26 - index}),
                  Date.from_erl!({2019, 08, 26 - index})
                ]

              [_, true] ->
                [
                  Date.from_erl!({2016, 08, 26 - index})
                ]

              [_, false] ->
                [Date.from_erl!({2019, 08, 26 - index})]
            end

          dates
          |> Enum.each(fn date ->
            Factory.create_stock_quote(%{
              close: close,
              date: date,
              symbol: symbol,
              volume: volume
            })
          end)
        end)
      end)

      assert %{
               "basket_movement" => -0.289443,
               "reference" => %{
                 "last_two_closes" => [
                   %{"close" => 372.06},
                   %{"close" => 933.57}
                 ],
                 "movement" => -0.601465,
                 "symbol" => "HOTT"
               }
             } = MovementCalculator.calculate("HOTT", date_limit: date_limit)
    end
  end

  defp stubbed_stock_quotes do
    # last_quote_close, last_quote_vol, penultimate_quote_close, penultimate_quote_vol, third_close, third_volume
    ~w[
      3.7206e+02   2.6224e+05   9.3357e+02   6.3718e+05   6.5232e+02   4.8821e+05
      2.3723e+02   4.9149e+05   3.0500e+02   1.3373e+04   8.4866e+02   1.1450e+05
      8.3617e+02   2.3985e+05   8.0350e+02   7.5613e+05   1.3247e+01   5.7128e+05
      9.8741e+02   3.2806e+05   7.8717e+02   1.1994e+05   1.0268e+02   1.7471e+04
      2.1186e+02   1.2202e+05   9.4379e+02   9.2037e+05   9.3438e+02   1.4152e+05
      3.0376e+02   6.5843e+05   9.2867e+02   6.0538e+04   4.9273e+01   3.8233e+05
    ]
    |> Enum.map(fn num ->
      magnitude =
        num
        |> String.split(~r/e\+/)
        |> Enum.at(1)
        |> String.to_integer()

      cond do
        magnitude <= 2 ->
          num |> String.to_float() |> Float.round(2)

        true ->
          num |> String.to_float() |> Kernel.trunc()
      end
    end)
    |> Enum.chunk_every(6)
  end
end
