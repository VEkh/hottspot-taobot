defmodule HottspotCapital.Basket.Generator do
  require Ecto.Query

  alias HottspotCapital.Repo
  alias HottspotCapital.SQLQueryParser
  alias HottspotCapital.StockQuote

  def basket_query() do
    """
    (
      SELECT
        sorted_basket.basket_item_symbol,
        sorted_basket.reference_symbol,
        sorted_basket.correlation

      FROM (
        SELECT
          DISTINCT ON (basket_item.sector)
          reference.symbol AS reference_symbol,
          basket_item.symbol AS basket_item_symbol,
          CORR(reference.close, basket_item.close) AS correlation

        FROM (
          SELECT
            companies.name AS company_name,
            stock_quotes.close,
            stock_quotes.date,
            stock_quotes.symbol

          FROM (
            SELECT close, date, symbol FROM stock_quotes
            WHERE symbol = $symbol
            AND date < $date_limit
          ) AS stock_quotes

          JOIN companies on companies.symbol = stock_quotes.symbol
        ) AS reference

        JOIN LATERAL (
          SELECT
            companies.sector,
            stock_quotes.close,
            stock_quotes.date,
            stock_quotes.symbol

          FROM (
            SELECT close, date, symbol FROM stock_quotes
            WHERE symbol != reference.symbol
            AND date < $date_limit
          ) AS stock_quotes

          JOIN (
            SELECT sector, symbol FROM companies
            WHERE name != reference.company_name
             AND symbol != reference.symbol
          ) AS companies on companies.symbol = stock_quotes.symbol
        ) AS basket_item ON reference.date = basket_item.date

        GROUP BY
          basket_item.sector,
          basket_item.symbol,
          reference.symbol

        HAVING CORR(reference.close, basket_item.close) IS NOT NULL
        ORDER BY basket_item.sector, 3 DESC
      ) AS sorted_basket

      ORDER BY sorted_basket.correlation DESC
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
