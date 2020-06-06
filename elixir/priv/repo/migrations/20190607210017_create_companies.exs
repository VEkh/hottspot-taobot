defmodule HottspotCapital.Repo.Migrations.CreateCompanies do
  use Ecto.Migration

  def up do
    [
      """
      CREATE TABLE companies (
        company_name text NOT NULL,
        inserted_at timestamptz NOT NULL default NOW(),
        market_cap bigint NOT NULL,
        symbol varchar(5) PRIMARY KEY,
        updated_at timestamptz NOT NULL default NOW()
      )
      """,
      """
      CREATE UNIQUE INDEX stock_quotes_symbol_date_index
        ON stock_quotes (date, symbol);
      """,
      """
      ALTER TABLE stock_quotes
        DROP CONSTRAINT stock_quotes_pkey,
        ADD COLUMN id SERIAL PRIMARY KEY,
        DROP COLUMN company_name,
        DROP COLUMN market_cap,
        ADD CONSTRAINT stock_quotes_symbol_fkey
          FOREIGN KEY (symbol) REFERENCES companies (symbol),
        ADD CONSTRAINT stock_quotes_symbol_date_index
          UNIQUE USING INDEX stock_quotes_symbol_date_index;
      """
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      """
      ALTER TABLE stock_quotes
        DROP COLUMN id,
        ADD PRIMARY KEY (symbol),
        ADD COLUMN company_name text,
        ADD COLUMN market_cap bigint,
        DROP CONSTRAINT stock_quotes_symbol_fkey,
        DROP CONSTRAINT stock_quotes_symbol_date_index;
      """,
      """
      UPDATE stock_quotes SET
      company_name = companies.company_name,
      market_cap = companies.market_cap
      FROM companies WHERE companies.symbol = stock_quotes.symbol;
      """,
      "DROP TABLE companies CASCADE",
      """
      ALTER TABLE stock_quotes
        ALTER COLUMN company_name SET NOT NULL,
        ALTER COLUMN market_cap SET NOT NULL;
      """
    ]
    |> Enum.each(&execute/1)
  end
end
