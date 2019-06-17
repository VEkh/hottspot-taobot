defmodule HottspotCapital.StockQuoteImporter do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import(symbol) do
    fetched_stock_quote =
      IexApiClient.fetch_stock_quote(symbol)
      |> parse_stock_quote()

    with stock_quote when not is_nil(stock_quote) <- fetched_stock_quote,
         {:ok, stock_quote} <-
           stock_quote
           |> StockQuote.changeset()
           |> StockQuote.upsert() do
      stock_quote
    end
  end

  defp parse_stock_quote(stock_quote) do
    %{
      "close" => close,
      "closeTime" => close_date_epoch,
      "latestVolume" => volume,
      "open" => open,
      "symbol" => symbol
    } = stock_quote

    close_date =
      close_date_epoch
      |> DateTime.from_unix!(:millisecond)
      |> DateTime.to_date()

    required_props = [close, open]

    cond do
      required_props |> Enum.all?(&(!is_nil(&1))) ->
        %{
          close: close / 1,
          date: close_date,
          open: open / 1,
          symbol: symbol,
          volume: volume
        }

      true ->
        nil
    end
  end
end
