defmodule HottspotCapital.Repo.Migrations.CreateFundTransactions do
  use Ecto.Migration

  def up do
    execute("""
      CREATE TABLE fund_transactions (
        amount integer NOT NULL,
        description text NOT NULL,
        id serial PRIMARY KEY,
        inserted_at timestamptz NOT NULL DEFAULT now(),
        updated_at timestamptz NOT NULL DEFAULT now()
      )
    """)
  end

  def down do
    execute("DROP TABLE fund_transactions")
  end
end
