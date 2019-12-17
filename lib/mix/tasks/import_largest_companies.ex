defmodule Mix.Tasks.ImportLargestCompanies do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.StockQuote
  alias Mix.Tasks.OptionsParser

  @default_options %{
    "limit" => 200
  }

  @name :import_largest_companies

  @permitted_options Map.keys(@default_options)

  @shortdoc "Import largest cap n companies"

  @moduledoc """
  #{@shortdoc}

  Arguments:

    They should be passed in the following the format: `--key=value`

    - limit: largest n companies (by market cap) to be imported. Default: 200

  Example:
  ```
  mix #{@name} --limit=200
  ```
  """

  def run(options \\ []) do
    Application.ensure_all_started(:hottspot_capital)

    %{"limit" => limit} =
      OptionsParser.parse(%{
        defaults: @default_options,
        options: options,
        permitted: @permitted_options,
        task_name: @name
      })
      |> cast_options()

    get_all_symbols()
    |> Stream.map(&IexApiClient.fetch_stock_quote/1)
    |> Stream.filter(&(!is_nil(&1)))
    |> Enum.sort(fn %{market_cap: a}, %{market_cap: b} -> a > b end)
    |> Enum.take(limit)
    |> Enum.map(fn %IexApiClient.StockQuote{symbol: symbol} = stock_quote_params ->
      params = Map.from_struct(stock_quote_params)

      {:ok, company} =
        params
        |> Company.changeset()
        |> Company.upsert()

      beta = IexApiClient.fetch_stock_beta(symbol)

      {:ok, _stock_quote} =
        params
        |> Map.put(:beta, beta)
        |> StockQuote.changeset()
        |> StockQuote.upsert()

      company
    end)
  end

  defp cast_options(options) do
    %{"limit" => limit} = options

    casted_options = %{
      "limit" => String.to_integer("#{limit}")
    }

    Map.merge(options, casted_options)
  end

  defp get_all_symbols() do
    symbols = IexApiClient.client().get("/ref-data/symbols")

    for %{
          "currency" => currency,
          "isEnabled" => is_enabled,
          "symbol" => symbol,
          "type" => type
        } <- symbols,
        currency === "USD" && is_enabled === true && type === "cs" do
      symbol
    end
  end
end
