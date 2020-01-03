defmodule HottspotCapital.StockQuote.ImporterTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuote.Importer
  alias HottspotCapital.Test.Factory

  describe ".import_historical" do
    test "imports daily stock quotes from the last n years" do
      symbol = "HOTT"
      Factory.create_company(%{symbol: symbol})
      Importer.import_historical(range: "1y", symbol: symbol)

      imported_stock_quotes = Repo.all(StockQuote)

      %{date: first_quote_date} = List.first(imported_stock_quotes)
      %{date: last_quote_date} = List.last(imported_stock_quotes)
      {first_quote_year, _, _} = Date.to_erl(first_quote_date)
      {last_quote_year, _, _} = Date.to_erl(last_quote_date)

      assert last_quote_year - first_quote_year == 1
    end
  end
end
