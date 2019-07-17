defmodule HottspotCapital.StockQuoteImporter do
  alias HottspotCapital.Company
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

  def import_historical(top_companies: count, years: years) do
    Company.get_largest(count)
    |> Enum.flat_map(fn
      %{symbol: symbol} -> import_historical(symbol, years: years)
    end)
  end

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
