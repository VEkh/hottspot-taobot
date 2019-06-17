defmodule HottspotCapital.CompanyImporter do
  alias HottspotCapital.Company
  alias HottspotCapital.IexApiClient

  def import_largest(count \\ 200) do
    get_all_symbols()
    |> Stream.map(&IexApiClient.fetch_stock_quote/1)
    |> Stream.map(&parse_stock_quote/1)
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
    symbols = IexApiClient.client().get("/ref-data/symbols")

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

  defp parse_stock_quote(nil), do: nil

  defp parse_stock_quote(stock_quote) do
    %{
      "companyName" => company_name,
      "close" => close,
      "marketCap" => market_cap,
      "open" => open,
      "symbol" => symbol
    } = stock_quote

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
