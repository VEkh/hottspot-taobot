defmodule HottspotCapital.Test.Factory do
  alias HottspotCapital.Company
  alias HottspotCapital.StockQuote

  def create_company(%{} = attributes) do
    defaults = %Company{
      market_cap: 1_000_000_000,
      name: Ecto.UUID.generate(),
      sector: Ecto.UUID.generate(),
      symbol: "HOTT"
    }

    {:ok, _} =
      defaults
      |> Company.changeset(attributes)
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

    {:ok, _} =
      defaults
      |> StockQuote.changeset(attributes)
      |> StockQuote.upsert()
  end
end
