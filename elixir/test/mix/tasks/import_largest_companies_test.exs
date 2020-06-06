defmodule Mix.Tasks.ImportLargestCompaniesTest do
  require Ecto.Query

  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Company
  alias HottspotCapital.Repo
  alias HottspotCapital.Test.Stubs.IexApiStubs
  alias Mix.Tasks.ImportLargestCompanies

  test "imports and persists companies" do
    ImportLargestCompanies.run(["--limit=10"])

    companies = Repo.all(Company)

    assert [%Company{sector: <<_::binary>>} | _] = companies
    assert length(companies) == 10
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
    bad_stats =
      IexApiStubs.company_stats()
      |> Map.put("marketcap", nil)

    Mocks.update(%{
      function: :get_company_stats,
      module: HottspotCapital.Test.Mocks.IexApiClient,
      value: bad_stats
    })

    assert ImportLargestCompanies.run() == []
  end
end
