defmodule HottspotCapital.BasketGenerator do
  require Ecto.Query

  alias HottspotCapital.Repo

  def generate(symbol) do
    %Postgrex.Result{rows: [[^symbol, basket]]} =
      """
      SELECT
        basket_query.reference_symbol AS symbol,
        JSON_AGG(
          JSON_BUILD_OBJECT(
            basket_query.basket_item_symbol,
            basket_query.correlation
          )
        ) AS basket
      FROM (
        SELECT reference.symbol AS reference_symbol,
        basket_item.symbol AS basket_item_symbol,
        corr(reference.close, basket_item.close) AS correlation

        FROM stock_quotes AS reference
        JOIN stock_quotes AS basket_item
          ON reference.date = basket_item.date
          AND reference.symbol != basket_item.symbol
        WHERE reference.symbol = $1
        GROUP BY reference.symbol, basket_item.symbol
        ORDER BY 3 DESC
        LIMIT 10
      ) AS basket_query
      GROUP BY basket_query.reference_symbol
      """
      |> Repo.query!([symbol])

    basket
  end
end
