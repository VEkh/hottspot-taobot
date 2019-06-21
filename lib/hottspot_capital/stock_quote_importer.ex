defmodule HottspotCapital.StockQuoteImporter do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import(symbol) do
    with %IexApiClient.StockQuote{} = fetched_stock_quote <-
           IexApiClient.fetch_stock_quote(symbol),
         {:ok, stock_quote} <-
           fetched_stock_quote
           |> Map.from_struct()
           |> StockQuote.changeset()
           |> StockQuote.upsert() do
      stock_quote
    end
  end
end
