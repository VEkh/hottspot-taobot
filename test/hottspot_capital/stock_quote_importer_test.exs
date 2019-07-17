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

    test "imports historical stocks from top n companies" do
      [
        %{market_cap: 8, symbol: "AMZN"},
        %{market_cap: 7, symbol: "FB"},
        %{market_cap: 6, symbol: "GOOG"},
        %{market_cap: 10, symbol: "HOTT"},
        %{market_cap: 9, symbol: "MSFT"}
      ]
      |> Enum.each(&Factory.create_company/1)

      StockQuoteImporter.import_historical(top_companies: 3, years: 5)
      stock_quotes = Repo.all(StockQuote)

      subject =
        stock_quotes
        |> Enum.reduce(
          %{},
          fn %{date: date, symbol: symbol}, acc ->
            {year, _, _} = Date.to_erl(date)

            years =
              (acc[symbol] || [])
              |> List.insert_at(-1, year)
              |> Enum.uniq()
              |> Enum.sort(fn a, b -> a < b end)

            Map.put(acc, symbol, years)
          end
        )

      assert %{
               "AMZN" => [2013, 2014, 2015, 2016, 2017, 2018],
               "HOTT" => [2013, 2014, 2015, 2016, 2017, 2018],
               "MSFT" => [2013, 2014, 2015, 2016, 2017, 2018]
             } = subject
    end
  end
end
