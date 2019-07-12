defmodule HottspotCapital.StockQuoteImporterTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuoteImporter
  alias HottspotCapital.Test.Factory

  describe ".import_historical" do
    test "imports daily stock quotes from the last n years" do
      symbol = "HOTT"
      Factory.create_company(%{symbol: symbol})
      StockQuoteImporter.import_historical(symbol, years: 1)

      imported_stock_quotes = Repo.all(StockQuote)

      %{date: first_quote_date} = List.first(imported_stock_quotes)
      %{date: last_quote_date} = List.last(imported_stock_quotes)
      {first_quote_year, _, _} = Date.to_erl(first_quote_date)
      {last_quote_year, _, _} = Date.to_erl(last_quote_date)

      assert last_quote_year - first_quote_year == 1
    end
  end
end
