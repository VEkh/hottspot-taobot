defmodule Mix.Tasks.ImportHistoricalTopStocks do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.StockQuote
  alias HottspotCapital.StockQuote.Importer
  alias Mix.Tasks.OptionsParser

  @default_options %{
    "companies_limit" => 200
  }

  @name :import_historical_top_stocks

  @permitted_options Map.keys(@default_options)

  @shortdoc "Import historical stock quotes for top n companies"

  @moduledoc """
  #{@shortdoc}

  Arguments:

   They should be passed in the following the format: `--key=value`

    - companies_limit: largest n companies (by market cap) whose historical
      data whould be imported. Default: 200

  Example:
  ```
  mix #{@name} --companies_limit=200
  ```
  """

  def run(options \\ []) do
    Application.ensure_all_started(:hottspot_capital)

    %{"companies_limit" => companies_limit} =
      OptionsParser.parse(%{
        defaults: @default_options,
        options: options,
        permitted: @permitted_options,
        task_name: @name
      })

    Company.get_largest(companies_limit)
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
