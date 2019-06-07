defmodule HottspotCapital.CompanyImporter do
  alias HottspotCapital.Company

  @iex_api_client Application.get_env(:hottspot_capital, :iex_api_client)[:module]

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

  defp get_all_symbols() do
    symbols = @iex_api_client.get("/ref-data/symbols")

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

  defp get_stock_quote(symbol) do
    "/stock/#{symbol}/quote"
    |> @iex_api_client.get()
    |> parse_stock_quote
  end

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
