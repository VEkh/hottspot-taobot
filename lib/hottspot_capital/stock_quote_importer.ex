defmodule HottspotCapital.StockQuoteImporter do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import_historical(symbol, years: years) do
    fetched_historical_quotes = IexApiClient.fetch_historical_stock_quotes(symbol, years: years)

    case fetched_historical_quotes do
      [%IexApiClient.HistoricalStockQuote{} | _] ->
        for fetched_historical_quote <- fetched_historical_quotes do
          {:ok, stock_quote} =
            fetched_historical_quote
            |> Map.from_struct()
            |> Map.put(:symbol, symbol)
            |> StockQuote.changeset()
            |> StockQuote.upsert()

          stock_quote
        end

      resp ->
        resp
    end
  end
end
