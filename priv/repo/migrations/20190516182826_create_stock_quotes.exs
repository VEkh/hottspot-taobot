defmodule HottspotCapital.Repo.Migrations.CreateStockQuotes do
  use Ecto.Migration

  def up do
    execute(~s[
      CREATE TABLE stock_quotes (
        close float NOT NULL,
        company_name text NOT NULL,
        date date NOT NULL,
        inserted_at timestamptz NOT NULL default NOW(),
        market_cap bigint NOT NULL,
        open float NOT NULL,
        symbol varchar(5) PRIMARY KEY,
        updated_at timestamptz NOT NULL default NOW(),
        volume bigint NOT NULL
      )
    ])
  end

  def down do
    execute("DROP TABLE stock_quotes")
  end
end
