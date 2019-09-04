defmodule HottspotCapital.StockQuote.Importer do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import(symbol) do
    fetched_stock_quote = IexApiClient.fetch_stock_quote(symbol)

    case fetched_stock_quote do
      %IexApiClient.StockQuote{} ->
        {:ok, stock_quote} =
          fetched_stock_quote
          |> Map.from_struct()
          |> StockQuote.changeset()
          |> StockQuote.upsert()

        stock_quote

      resp ->
        resp
    end
  end

  def import_historical(range: range, symbol: symbol) do
    quotes = IexApiClient.fetch_historical_stock_quotes(range: range, symbol: symbol)

    case quotes do
      [%IexApiClient.HistoricalStockQuote{} | _] ->
        for historical_quote <- quotes do
          {:ok, stock_quote} =
            historical_quote
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
