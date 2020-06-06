defmodule HottspotCapital.Basket.BuyRecommenderTest do
  use HottspotCapital.Test.DataCase, concurrent: true

  alias HottspotCapital.Basket.BuyRecommender
  alias HottspotCapital.Basket.Movement
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.StockQuoteStubs

  describe ".recommend" do
    setup do
      symbols = ["HOTT", "T", "VZ", "UBER", "NFLX"]

      symbols
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

      [symbols: symbols]
    end

    test "returns list of buy recommendation movements", %{symbols: symbols} do
      BuyRecommender.recommend()
      |> Enum.each(fn movement ->
        %Movement{
          basket_movement: basket_movement,
          reference: %{
            movement: reference_movement,
            symbol: symbol
          }
        } = movement

        assert is_float(basket_movement)
        assert is_float(reference_movement)
        assert symbol in symbols
      end)
    end

    test "returns list of buy recommendation symbols", %{symbols: symbols} do
      [format: :symbol]
      |> BuyRecommender.recommend()
      |> Enum.each(fn symbol ->
        assert is_binary(symbol)
        assert symbol in symbols
      end)
    end

    test "filter out companies who fail to return movements" do
      assert [] = BuyRecommender.recommend(date_limit: ~D[2018-12-31])
    end
  end

  defp stubbed_closes_and_volumes do
    # close        volume
    ~w[
      5.6263e+02   3.3211e+05
      1.5278e+02   1.7290e+05

      2.8143e+02   9.2477e+05
      3.1354e+01   3.9859e+05

      8.3755e+02   7.6846e+05
      1.7336e+02   8.0951e+05

      9.2679e+02   9.3753e+05
      4.0022e+02   4.2394e+05

      6.8492e+02   6.0986e+05
      9.9520e+02   8.9132e+05
    ]
    |> StockQuoteStubs.group_closes_and_volumes(days: 2)
  end
end
