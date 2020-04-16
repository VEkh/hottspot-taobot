defmodule HottspotCapital.StockQuote.Importer do
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote

  def import_historical(range: range, symbol: symbol) do
    quotes =
      IexApiClient.fetch_historical_stock_quotes(
        range: range,
        symbol: symbol
      )

    with [%IexApiClient.HistoricalStockQuote{} | _] <- quotes,
         beta when is_float(beta) <-
           IexApiClient.fetch_company_stat(stat: "beta", symbol: symbol) do
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
        List.wrap(resp)
    end
  end
end
