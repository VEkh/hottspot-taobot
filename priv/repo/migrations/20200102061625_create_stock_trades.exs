defmodule HottspotCapital.Repo.Migrations.CreateStockTrades do
  use Ecto.Migration

  def up do
    [
      "CREATE TYPE stock_trade_action AS ENUM ('buy', 'sell')",
      """
        CREATE TABLE stock_trades (
          action stock_trade_action NOT NULL,
          filled_at timestamptz NOT NULL,
          id serial PRIMARY KEY,
          inserted_at timestamptz NOT NULL DEFAULT now(),
          price integer NOT NULL,
          symbol text NOT NULL REFERENCES companies(symbol),
          updated_at timestamptz NOT NULL default now(),
          volume integer NOT NULL
        )
      """,
      "CREATE INDEX stock_trades_symbol_idx ON stock_trades(symbol)"
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "DROP TABLE stock_trades",
      "DROP TYPE stock_trade_action"
    ]
    |> Enum.each(&execute/1)
  end
end
