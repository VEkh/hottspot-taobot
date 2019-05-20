defmodule HottspotCapital.StockImporter do
  alias HottspotCapital.StockQuote

  @iex_api_client Application.get_env(:hottspot_capital, :iex_api_client)[:module]

  def import_largest(count \\ 200) do
    get_all_symbols()
    |> Stream.map(&get_stock/1)
    |> Stream.filter(&(!is_nil(&1)))
    |> Enum.sort(fn %{market_cap: a}, %{market_cap: b} -> a > b end)
    |> Enum.take(count)
    |> Enum.map(fn stock_quote_params ->
      # TODO: save as companies AND stock quotes
      # TODO: Import historical stock quote data from the two hundred biggest companies
      {:ok, stock_quote} =
        stock_quote_params
        |> StockQuote.changeset()
        |> StockQuote.upsert()

      stock_quote
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

  defp get_stock(symbol) do
    "/stock/#{symbol}/quote"
    |> @iex_api_client.get()
    |> parse_stock
  end

  defp parse_stock(stock) do
    %{
      "companyName" => company_name,
      "close" => close,
      "closeTime" => close_epoch,
      "latestVolume" => volume,
      "marketCap" => market_cap,
      "open" => open,
      "symbol" => symbol
    } = stock

    required_props = [close, open]

    with true <- required_props |> Enum.all?(&(!is_nil(&1))),
         {:ok, close_datetime} <- DateTime.from_unix(close_epoch, :millisecond) do
      close_date = DateTime.to_date(close_datetime)

      %{
        close: close / 1,
        company_name: company_name,
        date: close_date,
        market_cap: market_cap,
        open: open / 1,
        symbol: symbol,
        volume: volume
      }
    else
      _ -> nil
    end
  end
end
