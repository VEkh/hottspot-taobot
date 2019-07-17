defmodule HottspotCapital.Test.Factory do
  alias HottspotCapital.Company

  def create_company(%{} = attributes) do
    defaults = %Company{
      company_name: "Hottspot, Inc",
      market_cap: 1_000_000_000,
      symbol: "HOTT"
    }

    Company.changeset(defaults, attributes)
    |> Company.upsert()
  end
end
