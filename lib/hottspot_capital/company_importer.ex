defmodule HottspotCapital.CompanyImporter do
  alias HottspotCapital.Company

  def import_largest(count \\ 200) do
    get_all_symbols()
    |> Stream.map(&get_stock_quote/1)
    |> Stream.filter(&(!is_nil(&1)))
    |> Enum.sort(fn %{market_cap: a}, %{market_cap: b} -> a > b end)
    |> Enum.take(count)
    |> Enum.map(fn company_params ->
      {:ok, company} =
        company_params
        |> Company.changeset()
        |> Company.upsert()

      company
    end)
  end

  defp config, do: Application.get_env(:hottspot_capital, :iex_api_client)

  defp get_all_symbols() do
    symbols = iex_api_client().get("/ref-data/symbols")

    for %{
          "currency" => currency,
          "isEnabled" => is_enabled,
          "symbol" => symbol,
          "type" => type
        } <- symbols,
        currency === "USD" && is_enabled === true && type === "cs" do
      symbol
    end
  end

  defp get_stock_quote(symbol, attempt \\ 1) do
    response = iex_api_client().get("/stock/#{symbol}/quote")

    case [response, attempt] do
      [%{"symbol" => _} = resp, _] ->
        parse_stock_quote(resp)

      [{:ok, %{status_code: 502}}, current_attempt] when current_attempt < 3 ->
        retry_wait = config()[:request_retry_wait]
        Process.sleep(retry_wait)
        get_stock_quote(symbol, attempt + 1)

      [{:ok, %{status_code: 502}}, _] ->
        nil
    end
  end

  defp iex_api_client(), do: config()[:module]

  defp parse_stock_quote(stock) do
    %{
      "companyName" => company_name,
      "close" => close,
      "marketCap" => market_cap,
      "open" => open,
      "symbol" => symbol
    } = stock

    required_props = [close, open]

    cond do
      required_props |> Enum.all?(&(!is_nil(&1))) ->
        %{
          company_name: company_name,
          market_cap: market_cap,
          symbol: symbol
        }

      true ->
        nil
    end
  end
end
