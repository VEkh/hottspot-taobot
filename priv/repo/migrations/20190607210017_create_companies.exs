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
      ALTER TABLE stock_quotes
        DROP COLUMN company_name,
        DROP COLUMN market_cap,
        ADD CONSTRAINT stock_quotes_symbol_fkey
          FOREIGN KEY (symbol) REFERENCES companies (symbol)
      """
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "DROP TABLE companies CASCADE",
      """
      ALTER TABLE stock_quotes
        ADD COLUMN company_name text NOT NULL,
        ADD COLUMN market_cap bigint NOT NULL;
      """
    ]
    |> Enum.each(&execute/1)
  end
end
