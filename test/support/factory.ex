defmodule HottspotCapital.Test.Factory do
  alias HottspotCapital.Company

  def create_company(%{} = attributes) do
    defaults = %Company{
      company_name: "HOTT",
      market_cap: 1_000_000_000,
      symbol: "Hottspot, Inc"
    }

    Company.changeset(defaults, attributes)
    |> Company.upsert()
  end
end
