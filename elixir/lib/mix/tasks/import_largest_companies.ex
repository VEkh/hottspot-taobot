defmodule Mix.Tasks.ImportLargestCompanies do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.IexApiClient
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
    |> Enum.flat_map(&init_company/1)
    |> Enum.sort(fn %{market_cap: a}, %{market_cap: b} -> a > b end)
    |> Enum.take(limit)
    |> Enum.map(&upsert_company/1)
  end

  defp build_company_params(%{symbol: symbol} = company) do
    symbol
    |> IexApiClient.fetch_company()
    |> Map.merge(%{
      company
      | beta: IexApiClient.fetch_company_stat(stat: :beta, symbol: symbol)
    })
    |> Map.from_struct()
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

  defp init_company(symbol) do
    case IexApiClient.fetch_company_stat(stat: :marketcap, symbol: symbol) do
      nil -> []
      market_cap -> [%{beta: nil, market_cap: market_cap, symbol: symbol}]
    end
  end

  defp upsert_company(params) do
    {:ok, company} =
      params
      |> build_company_params()
      |> Company.changeset()
      |> Company.upsert()

    company
  end
end
