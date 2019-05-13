defmodule HottspotCapital.StockImporterTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Repo
  alias HottspotCapital.StockImporter
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.DynamicMocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  describe ".import_largest" do
    test "imports and persists stocks" do
      imported_stocks = StockImporter.import_largest(10)

      assert length(imported_stocks) == 10

      assert [
               %StockQuote{
                 close: 1788.5,
                 company_name: _,
                 date: ~D[2021-06-09],
                 market_cap: _,
                 open: 1837.0,
                 symbol: _,
                 volume: 3_355_103
               }
               | _
             ] = imported_stocks

      assert Repo.all(StockQuote) |> length() == 10
    end

    test "sorts stocks by market cap" do
      imported_stocks = StockImporter.import_largest(10)

      [market_cap1, market_cap2, market_cap3 | _] =
        for %{market_cap: market_cap} <- imported_stocks, do: market_cap

      assert market_cap1 > market_cap2 && market_cap2 > market_cap3
    end

    test "does not import stocks with unusable symbols" do
      base_symbol = IexApiStubs.base_symbol("HOTT")

      bad_symbols = [
        base_symbol |> Map.put("type", "ps"),
        base_symbol |> Map.put("isEnabled", false),
        base_symbol |> Map.put("currency", "EU")
      ]

      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: bad_symbols
      })

      assert StockImporter.import_largest() == []
    end

    test "does not import stocks with unusable data" do
      base_symbol = IexApiStubs.base_symbol("HOTT")

      bad_symbols =
        ["NIL_CLOSE", "NIL_OPEN"]
        |> Enum.map(&Map.put(base_symbol, "symbol", &1))

      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [base_symbol] ++ bad_symbols
      })

      assert [%StockQuote{symbol: "HOTT"} | []] = StockImporter.import_largest()
    end
  end
end
