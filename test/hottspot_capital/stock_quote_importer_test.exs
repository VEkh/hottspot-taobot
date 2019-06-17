defmodule HottspotCapital.StockQuoteImporterTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuoteImporter
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.IexApiStubs

  describe ".import" do
    test "imports and persists stock quote" do
      Factory.create_company(%{symbol: "HOTT"})

      assert %StockQuote{
               close: _,
               date: _,
               open: _,
               symbol: _,
               volume: _
             } = StockQuoteImporter.import("HOTT")

      assert Repo.all(StockQuote) |> length() == 1
    end

    test "doesn't persist stock with usesless data" do
      DynamicMocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: IexApiStubs.stock_quote("NIL_CLOSE")
      })

      assert StockQuoteImporter.import("HOTT") == nil
    end
  end
end
