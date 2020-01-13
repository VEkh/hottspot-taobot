defmodule HottspotCapital.Repo.Migrations.CreateStockPositionsAndTrades do
  use Ecto.Migration

  def up do
    [
      """
      CREATE TABLE stock_buys (
        id SERIAL PRIMARY KEY,
        executed_at timestamptz NOT NULL,
        inserted_at timestamptz NOT NULL DEFAULT now(),
        price integer NOT NULL,
        symbol text NOT NULL REFERENCES companies(symbol),
        updated_at timestamptz NOT NULL DEFAULT now(),
        volume integer NOT NULL
      )
      """,
      """
      ALTER TABLE stock_buys
        ADD CONSTRAINT stock_buys_executed_at_symbol_key UNIQUE (executed_at, symbol)
      """,
      """
      CREATE TABLE stock_sells (
        id SERIAL PRIMARY KEY,
        executed_at timestamptz NOT NULL,
        inserted_at timestamptz NOT NULL DEFAULT now(),
        price integer NOT NULL,
        symbol text NOT NULL REFERENCES companies(symbol),
        updated_at timestamptz NOT NULL DEFAULT now(),
        volume integer NOT NULL
      )
      """,
      """
      ALTER TABLE stock_sells
        ADD CONSTRAINT stock_sells_executed_at_symbol_key UNIQUE (executed_at, symbol)
      """,
      """
      CREATE TABLE stock_positions (
        inserted_at timestamptz NOT NULL DEFAULT now(),
        stock_buy_id integer REFERENCES stock_buys(id),
        stock_sell_id integer REFERENCES stock_sells(id),
        updated_at timestamptz NOT NULL DEFAULT now()
      )
      """,
      """
      CREATE UNIQUE INDEX stock_positions_stock_buy_id_idx
        ON stock_positions(stock_buy_id)
      """,
      """
      CREATE UNIQUE INDEX stock_positions_stock_sell_id_idx
        ON stock_positions(stock_sell_id)
      """,
      """
      ALTER TABLE stock_positions
        ADD CONSTRAINT stock_positions_opening_trade_check CHECK (
          (
            (stock_buy_id IS NOT NULL)::int +
            (stock_sell_id IS NOT NULL)::int
          ) > 0
        )
      """
    ]
    |> Enum.each(&execute/1)
  end

  def down do
    [
      "DROP TABLE stock_positions",
      "DROP TABLE stock_buys",
      "DROP TABLE stock_sells"
    ]
    |> Enum.each(&execute/1)
  end
end
