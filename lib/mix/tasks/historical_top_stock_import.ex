defmodule Mix.Tasks.HistoricalTopStockImport do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuote.Importer

  @default_options %{
    "companies_limit" => 200
  }

  @permitted_options Map.keys(@default_options)

  @moduledoc """
  Import historical stock quotes for largest cap n companies.

  Arguments:
    They should be passed in the following the format: `--key=value`

    - companies_limit: largest n companies (by market cap)
    whose historical data whould be imported. Default: 200

  Example:
  ```
  mix historical_top_stock_import --companies_limit=200
  ```
  """

  @shortdoc "Import historical stock quotes for top n companies"
  def run(options) do
    %{"companies_limit" => companies_limit} = parse_options(options)

    Company.get_largest(companies_limit)
    |> Enum.flat_map(fn
      %{symbol: symbol} ->
        range = StockQuote.missing_data_range(symbol)
        log_import(range: range, symbol: symbol)
        Importer.import_historical(range: range, symbol: symbol)
    end)
  end

  defp log_import(range: range, symbol: symbol) do
    if Mix.env() != :test do
      IO.puts("Importing #{symbol}'s stock quotes for the past #{range}")
    end
  end

  defp parse_options(options) do
    options
    |> Enum.reduce(@default_options, fn option, acc ->
      case String.split(option, ["--", "="], trim: true) do
        [key, value] when key in @permitted_options ->
          Map.put(acc, key, value)

        _ ->
          error_message =
            "Invalid args #{options}. Run mix help historical_top_stock_import for help."

          raise(ArgumentError, message: error_message)
      end
    end)
  end
end
