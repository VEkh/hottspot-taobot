defmodule Mix.Tasks.UpdateCompanies do
  use Mix.Task

  alias HottspotCapital.Company
  alias HottspotCapital.IexApiClient
  alias HottspotCapital.Repo

  @name :update_companies

  @shortdoc "Update companies with IEX data"

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
    |> Enum.each(fn %{symbol: symbol} = company ->
      %IexApiClient.Company{
        name: <<_::binary>> = name,
        sector: <<_::binary>> = sector
      } = IexApiClient.fetch_company(symbol)

      company
      |> Map.from_struct()
      |> Map.merge(%{name: name, sector: sector})
      |> Company.changeset()
      |> Company.upsert()
    end)
  end
end
