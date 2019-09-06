defmodule HottspotCapital.IexApiClientTest do
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.IexApiClient
  alias HottspotCapital.Test.Stubs.IexApiStubs

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
      assert IexApiClient.fetch_historical_stock_quotes(range: :no_missing_data, symbol: "HOTT") ==
               []
    end
  end

  describe ".fetch_stock_quote" do
    test "returns nil for invalid stock quotes" do
      [
        "close",
        "closeTime",
        "open"
      ]
      |> Enum.each(fn nil_param_key ->
        bad_stock_quote =
          IexApiStubs.stock_quote("HOTT")
          |> Map.merge(%{nil_param_key => nil})

        Mocks.update(%{
          function: :get_stock,
          module: HottspotCapital.Test.Mocks.IexApiClient,
          value: bad_stock_quote
        })

        assert IexApiClient.fetch_stock_quote("HOTT") == nil
      end)
    end
  end

  describe ".fetch_stock_quote (unmocked IexApiClient)" do
    setup :unmock_iex_api_client

    test "returns nil on 404 response" do
      Mocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      Mocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:ok, %{body: Jason.encode!(%{}), status_code: 404}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil
    end

    test "retries 502 response" do
      Mocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      Mocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:ok, %{body: Jason.encode!(%{}), status_code: 502}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil
    end

    test "retries when there are timeout and connection issues" do
      Mocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      Mocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:error, %{reason: :timeout}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil

      Mocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:error, %{reason: :closed}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil
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
