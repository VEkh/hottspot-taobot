defmodule HottspotCapital.CompanyImporterTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Company
  alias HottspotCapital.CompanyImporter
  alias HottspotCapital.Repo
  alias HottspotCapital.Test.DynamicMocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  describe ".import_largest" do
    test "imports and persists companies" do
      imported_companies = CompanyImporter.import_largest(10)

      assert length(imported_companies) == 10

      assert [
               %Company{company_name: _, market_cap: _, symbol: _}
               | _
             ] = imported_companies

      assert Repo.all(Company) |> length() == 10
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

    test "retries 502 response of GET /stock/<symbol>/quote" do
      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      DynamicMocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: {:ok, %{body: %{}, status_code: 502}}
      })

      with_env(
        :hottspot_capital,
        :iex_api_client,
        [request_retry_wait: 1],
        fn ->
          assert [] = CompanyImporter.import_largest()
        end
      )
    end
  end

  defp with_env(app, key, options, fun) do
    old_values = Application.get_env(app, key)
    new_values = Keyword.merge(old_values, options)

    Application.put_env(app, key, new_values)

    try do
      fun.()
    after
      Application.put_env(app, key, old_values)
    end
  end
end
