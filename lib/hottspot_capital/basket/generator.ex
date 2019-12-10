defmodule HottspotCapital.Basket.Generator do
  require Ecto.Query

  alias HottspotCapital.Repo
  alias HottspotCapital.SQLQueryParser
  alias HottspotCapital.StockQuote

  def basket_query() do
    """
    (
      SELECT reference.symbol AS reference_symbol,
      basket_item.symbol AS basket_item_symbol,
      CORR(reference.close, basket_item.close) AS correlation

      FROM (
        SELECT close, date, symbol FROM stock_quotes
        WHERE symbol = $symbol
        AND date < $date_limit
      ) AS reference

      JOIN (
        SELECT close, date, symbol FROM stock_quotes
        WHERE symbol != $symbol
        AND date < $date_limit
      ) AS basket_item
        ON reference.date = basket_item.date

      GROUP BY reference.symbol, basket_item.symbol
      HAVING CORR(reference.close, basket_item.close) IS NOT NULL
      ORDER BY 3 DESC
      LIMIT 10
    )
    """
  end

  def generate(symbol, options \\ []) do
    %{date_limit: date_limit} =
      options
      |> Keyword.put(:symbol, symbol)
      |> merge_options()

    {query, params} =
      """
      SELECT
        basket_query.reference_symbol AS symbol,
        JSON_AGG(
          JSON_BUILD_OBJECT(
            basket_query.basket_item_symbol,
            basket_query.correlation
          )
        ) AS basket
      FROM #{basket_query()} AS basket_query
      GROUP BY basket_query.reference_symbol
      """
      |> SQLQueryParser.named_to_ordered_params(
        date_limit: date_limit,
        symbol: symbol
      )

    %Postgrex.Result{rows: rows} = Repo.query!(query, params)

    case rows do
      [[^symbol, basket]] -> basket
      [] -> []
    end
  end

  def merge_options([_ | _] = options) do
    options
    |> Enum.into(%{})
    |> merge_options()
  end

  def merge_options(%{date_limit: _date_limit} = options), do: options

  def merge_options(%{symbol: symbol} = options) do
    date_limit = most_recent_stock_quote_date(symbol)

    options
    |> Map.put(:date_limit, date_limit)
    |> merge_options()
  end

  defp most_recent_stock_quote_date(symbol) do
    Ecto.Query.from(
      stock_quotes in StockQuote,
      limit: 1,
      order_by: [desc: :date],
      select: stock_quotes.date,
      where: stock_quotes.symbol == ^symbol
    )
    |> Repo.one()
  end
end
