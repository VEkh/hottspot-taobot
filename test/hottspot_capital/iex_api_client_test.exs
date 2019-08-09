defmodule HottspotCapital.IexApiClientTest do
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.IexApiClient
  alias HottspotCapital.Test.Stubs.IexApiStubs

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

        DynamicMocks.update(%{
          function: :get_stock,
          module: HottspotCapital.Test.Mocks.IexApiClient,
          value: bad_stock_quote
        })

        assert IexApiClient.fetch_stock_quote("HOTT") == nil
      end)
    end
  end

  describe ".fetch_stock_quote (with HottspotCapital.IexApiClient)" do
    setup do
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

    test "returns nil on 404 response" do
      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      DynamicMocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:ok, %{body: %{}, status_code: 404}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil
    end

    test "retries 502 response" do
      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      DynamicMocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.HTTPoison,
        value: {:ok, %{body: %{}, status_code: 502}}
      })

      assert IexApiClient.fetch_stock_quote("HOTT") == nil
    end
  end
end
