defmodule HottspotCapital.StockQuote.Importer do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import(symbol) do
    fetched_stock_quote = IexApiClient.fetch_stock_quote(symbol)

    with %IexApiClient.StockQuote{} <- fetched_stock_quote,
         beta when is_number(beta) <- IexApiClient.fetch_stock_beta(symbol) do
      {:ok, stock_quote} =
        fetched_stock_quote
        |> Map.from_struct()
        |> Map.put(:beta, beta)
        |> StockQuote.changeset()
        |> StockQuote.upsert()

      stock_quote
    else
      resp ->
        resp
    end
  end

  def import_historical(range: range, symbol: symbol) do
    quotes =
      IexApiClient.fetch_historical_stock_quotes(
        range: range,
        symbol: symbol
      )

    with [%IexApiClient.HistoricalStockQuote{} | _] <- quotes,
         beta when is_number(beta) <- IexApiClient.fetch_stock_beta(symbol) do
      for historical_quote <- quotes do
        {:ok, stock_quote} =
          historical_quote
          |> Map.from_struct()
          |> Map.merge(%{beta: beta, symbol: symbol})
          |> StockQuote.changeset()
          |> StockQuote.upsert()

        stock_quote
      end
    else
      resp ->
        resp
    end
  end
end
