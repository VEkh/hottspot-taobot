defmodule Mix.Tasks.ImportLargestCompaniesTest do
  require Ecto.Query

  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Company
  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Stubs.IexApiStubs
  alias Mix.Tasks.ImportLargestCompanies

  test "imports and persists companies" do
    ImportLargestCompanies.run(["--limit=10"])

    company_symbols =
      Ecto.Query.from(company in Company, select: company.symbol)
      |> Repo.all()

    stock_quote_symbols =
      Ecto.Query.from(stock_quote in StockQuote, select: stock_quote.symbol)
      |> Repo.all()

    assert company_symbols == stock_quote_symbols
    assert length(company_symbols) == 10 && length(stock_quote_symbols) == 10
  end

  test "sorts companies by market cap" do
    imported_companies = ImportLargestCompanies.run(["--limit=10"])

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

    Mocks.update(%{
      function: :get_symbols,
      module: HottspotCapital.Test.Mocks.IexApiClient,
      value: bad_symbols
    })

    assert ImportLargestCompanies.run() == []
  end

  test "does not import companies with unusable data" do
    base_symbol = IexApiStubs.base_symbol("HOTT")

    bad_symbols =
      ["NIL_CLOSE", "NIL_OPEN"]
      |> Enum.map(&Map.put(base_symbol, "symbol", &1))

    Mocks.update(%{
      function: :get_symbols,
      module: HottspotCapital.Test.Mocks.IexApiClient,
      value: [base_symbol] ++ bad_symbols
    })

    assert [%Company{symbol: "HOTT"} | []] = ImportLargestCompanies.run()
  end
end
