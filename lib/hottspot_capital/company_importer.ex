defmodule HottspotCapital.CompanyImporter do
  alias HottspotCapital.Company
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import_largest(count \\ 200) do
    get_all_symbols()
    |> Stream.map(&IexApiClient.fetch_stock_quote/1)
    |> Stream.filter(&(!is_nil(&1)))
    |> Enum.sort(fn %{market_cap: a}, %{market_cap: b} -> a > b end)
    |> Enum.take(count)
    |> Enum.map(fn %IexApiClient.StockQuote{} = stock_quote_params ->
      params = Map.from_struct(stock_quote_params)

      {:ok, company} =
        params
        |> Company.changeset()
        |> Company.upsert()

      {:ok, _stock_quote} =
        params
        |> StockQuote.changeset()
        |> StockQuote.upsert()

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
end
