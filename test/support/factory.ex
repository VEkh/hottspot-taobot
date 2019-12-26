defmodule HottspotCapital.Test.Factory do
  alias HottspotCapital.Company
  alias HottspotCapital.StockQuote

  def create_company(%{} = attributes) do
    defaults = %Company{
      company_name: "Hottspot, Inc",
      market_cap: 1_000_000_000,
      sector: "Technology",
      symbol: "HOTT"
    }

    Company.changeset(defaults, attributes)
    |> Company.upsert()
  end

  def create_stock_quote(%{} = attributes) do
    defaults = %StockQuote{
      beta: 1.0,
      close: 1000.00,
      date: Date.utc_today(),
      open: 1000.00,
      symbol: "HOTT",
      volume: 1_000_000
    }

    StockQuote.changeset(defaults, attributes)
    |> StockQuote.upsert()
  end
end
