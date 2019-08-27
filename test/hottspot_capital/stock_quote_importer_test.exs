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
      Mocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: IexApiStubs.stock_quote("NIL_CLOSE")
      })

      assert StockQuoteImporter.import("HOTT") == nil
    end
  end

  describe ".import_historical" do
    test "imports daily stock quotes from the last n years" do
      symbol = "HOTT"
      Factory.create_company(%{symbol: symbol})
      StockQuoteImporter.import_historical(range: "1y", symbol: symbol)

      imported_stock_quotes = Repo.all(StockQuote)

      %{date: first_quote_date} = List.first(imported_stock_quotes)
      %{date: last_quote_date} = List.last(imported_stock_quotes)
      {first_quote_year, _, _} = Date.to_erl(first_quote_date)
      {last_quote_year, _, _} = Date.to_erl(last_quote_date)

      assert last_quote_year - first_quote_year == 1
    end
  end
end
