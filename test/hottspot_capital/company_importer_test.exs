defmodule HottspotCapital.CompanyImporterTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  import Ecto.Query, only: [from: 2]
  alias HottspotCapital.Company
  alias HottspotCapital.CompanyImporter
  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Stubs.IexApiStubs

  describe ".import_largest" do
    test "imports and persists companies" do
      CompanyImporter.import_largest(10)

      company_symbols =
        from(company in Company, select: company.symbol)
        |> Repo.all()

      stock_quote_symbols =
        from(stock_quote in StockQuote, select: stock_quote.symbol)
        |> Repo.all()

      assert company_symbols == stock_quote_symbols
      assert length(company_symbols) == 10 && length(stock_quote_symbols) == 10
    end

    test "sorts companies by market cap" do
      imported_companies = CompanyImporter.import_largest(10)

      [market_cap1, market_cap2, market_cap3 | _] =
        for %{market_cap: market_cap} <- imported_companies, do: market_cap

      assert market_cap1 > market_cap2 && market_cap2 > market_cap3
    end

    test "does not import companies with unusable symbols" do
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

      assert CompanyImporter.import_largest() == []
    end

    test "does not import companies with unusable data" do
      base_symbol = IexApiStubs.base_symbol("HOTT")

      bad_symbols =
        ["NIL_CLOSE", "NIL_OPEN"]
        |> Enum.map(&Map.put(base_symbol, "symbol", &1))

      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [base_symbol] ++ bad_symbols
      })

      assert [%Company{symbol: "HOTT"} | []] = CompanyImporter.import_largest()
    end
  end
end
