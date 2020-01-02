defmodule Mix.Tasks.ImportHistoricalStockQuotes do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuote.Importer

  @name :import_historical_stock_quotes

  @shortdoc "Import historical stock quotes for all companies"

  @moduledoc """
  #{@shortdoc}

  Example:
  ```
  mix #{@name}
  ```
  """

  def run(_) do
    Application.ensure_all_started(:hottspot_capital)

    Company
    |> Repo.all()
    |> Enum.flat_map(fn
      %{symbol: symbol} ->
        range = StockQuote.missing_data_range(symbol)
        log_import(env: Mix.env(), range: range, symbol: symbol)
        Importer.import_historical(range: range, symbol: symbol)
    end)
  end

  defp log_import(env: :test, range: _, symbol: _), do: nil

  defp log_import(env: _, range: range, symbol: symbol) do
    case range do
      :no_missing_data -> "#{symbol} is not missing any data"
      _ -> "Importing #{symbol}'s stock quotes for the past #{range}"
    end
    |> IO.puts()
  end
end
