defmodule HottspotCapital.ImportTopStocksTest do
  use ExUnit.Case

  alias HottspotCapital.ImportTopStocks

  describe ".import" do
    test "imports stocks" do
      assert [
               %{
                 close: 98.00,
                 current_volatility: 98.00,
                 date: "",
                 open: 98.00,
                 symbol: "HOTT",
                 volume: 1_000_000
               }
             ] = ImportTopStocks.import()
    end
  end
end
