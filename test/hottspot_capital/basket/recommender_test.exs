defmodule HottspotCapital.Basket.RecommenderTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Basket.Recommender
  alias HottspotCapital.Repo
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.StockQuoteStubs

  describe ".recommend" do
    setup do
      ["HOTT", "T", "VZ", "UBER", "NFLX"]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {symbol, data} ->
        Factory.create_company(%{symbol: symbol})

        data
        |> Enum.chunk_every(2)
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

      Ecto.Adapters.SQL.Sandbox.mode(Repo, {:shared, self()})
    end

    test "returns list of buy recommendations" do
      assert ["NFLX"] = Recommender.recommend()
    end
  end

  defp stubbed_closes_and_volumes do
    # close_1      volume_1     close_2      volume_2
    ~w[
      5.6263e+02   3.3211e+05   1.5278e+02   1.7290e+05
      2.8143e+02   9.2477e+05   3.1354e+01   3.9859e+05
      8.3755e+02   7.6846e+05   1.7336e+02   8.0951e+05
      9.2679e+02   9.3753e+05   4.0022e+02   4.2394e+05
      6.8492e+02   6.0986e+05   9.9520e+02   8.9132e+05
    ]
    |> StockQuoteStubs.group_closes_and_volumes(chunk_size: 4)
  end
end
