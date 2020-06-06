defmodule HottspotCapital.Repo.Migrations.AddBetaToStockQuotes do
  use Ecto.Migration

  def up do
    execute("""
    ALTER TABLE stock_quotes
      ADD COLUMN beta float NOT NULL DEFAULT 1.0
    """)
  end

  def down do
    execute("ALTER TABLE stock_quotes DROP COLUMN beta")
  end
end
