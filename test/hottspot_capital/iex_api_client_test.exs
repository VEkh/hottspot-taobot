defmodule HottspotCapital.IexApiClientTest do
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.IexApiClient

  describe ".fetch_company" do
    test "fetches company" do
      assert %HottspotCapital.IexApiClient.Company{
               name: <<_::binary>>,
               sector: <<_::binary>>,
               symbol: "HOTT"
             } = IexApiClient.fetch_company("HOTT")
    end
  end

  describe ".fetch_company_stat" do
    test "fetches company's single stat" do
      Mocks.update(%{
        function: :get_company_stats,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: %{
          "beta" => -0.444,
          "marketcap" => 444_444_444_444
        }
      })

      assert IexApiClient.fetch_company_stat(
               stat: "beta",
               symbol: "HOTT"
             ) == -0.444

      assert IexApiClient.fetch_company_stat(
               stat: "marketcap",
               symbol: "HOTT"
             ) == 444_444_444_444
    end
  end

  describe ".fetch_historical_stock_quotes (unmocked IexApiClient)" do
    setup :unmock_iex_api_client

    test "returns [] when empty collection is returned" do
      Mocks.update(%{
        function: :get_historical_stock_quotes,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:ok, %{body: Jason.encode!([]), status_code: 200}}
      })

      assert IexApiClient.fetch_historical_stock_quotes(range: "5y", symbol: "HOTT") == []
    end

    test "returns [] when range is :no_missing_data" do
      assert IexApiClient.fetch_historical_stock_quotes(
               range: :no_missing_data,
               symbol: "HOTT"
             ) == []
    end
  end

  defp unmock_iex_api_client(_context) do
    old_values = Application.get_env(:hottspot_capital, :iex_api_client)

    new_values =
      Keyword.merge(
        old_values,
        module: HottspotCapital.IexApiClient,
        request_retry_wait: 1
      )

    Application.put_env(:hottspot_capital, :iex_api_client, new_values)

    on_exit(fn ->
      Application.put_env(:hottspot_capital, :iex_api_client, old_values)
    end)

    :ok
  end
end
