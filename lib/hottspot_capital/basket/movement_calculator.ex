defmodule HottspotCapital.Basket.MovementCalculator do
  alias HottspotCapital.Basket.Generator
  alias HottspotCapital.Repo
  alias HottspotCapital.SQLQueryParser

  def calculate(symbol) do
    {reference, basket} = get_last_two_stock_quotes(symbol)

    %{
      "basket_movement" => calculate_basket_movement(basket),
      "reference" => reference_with_movement(reference)
    }
  end

  defp calculate_basket_movement(basket) do
    basket = Map.values(basket)

    [last_weighted_close, penultimate_weighted_close] =
      weigh_closes(
        basket: basket,
        total_weights: weigh_stock_quotes(basket)
      )

    movement(from: penultimate_weighted_close, to: last_weighted_close)
  end

  defp get_last_two_stock_quotes(symbol) do
    {query, params} =
      """
      SELECT
        stock_quotes.symbol,
        (ARRAY_AGG(
          JSON_BUILD_OBJECT(
            'date', stock_quotes.date,
            'close', stock_quotes.close,
            'volume', stock_quotes.volume
          )
          ORDER BY stock_quotes.date DESC
        ))[1:2] AS last_two_quotes
      FROM (
        SELECT (
          basket_query.reference_symbol ||
          ARRAY_AGG(basket_query.basket_item_symbol)
        ) AS symbols
        FROM #{Generator.basket_query()} AS basket_query
        GROUP BY basket_query.reference_symbol
      ) AS reference_and_basket
      JOIN stock_quotes
        ON ARRAY[stock_quotes.symbol] <@ reference_and_basket.symbols
      GROUP BY 1
      """
      |> SQLQueryParser.named_to_ordered_params(symbol: symbol)

    query
    |> Repo.query!(params)
    |> Map.get(:rows)
    |> Enum.reduce({%{}, %{}}, fn [sym, quotes], {reference, basket} ->
      case sym do
        ^symbol -> {Map.put(reference, sym, quotes), basket}
        _ -> {reference, Map.put(basket, sym, quotes)}
      end
    end)
  end

  defp movement(from: from, to: to) do
    ((to - from) / from)
    |> Float.round(6)
  end

  defp reference_with_movement(reference) do
    reference
    |> Enum.reduce(%{}, fn {symbol, closes}, acc ->
      [
        %{"close" => last_close},
        %{"close" => penultimate_close}
      ] = closes

      Map.merge(
        acc,
        %{
          "last_two_closes" => closes,
          "movement" => movement(from: penultimate_close, to: last_close),
          "symbol" => symbol
        }
      )
    end)
  end

  defp weigh_closes(basket: basket, total_weights: total_weights) do
    basket
    |> Enum.reduce([0, 0], fn stock_quotes, closes ->
      [closes, stock_quotes, total_weights]
      |> Enum.zip()
      |> Enum.map(fn {close, stock_quote, total_weight} ->
        %{
          "close" => stock_quote_close,
          "volume" => volume
        } = stock_quote

        close + stock_quote_close * volume / total_weight
      end)
    end)
  end

  defp weigh_stock_quotes(basket) do
    basket
    |> Enum.reduce([0, 0], fn stock_quotes, total_weights ->
      total_weights
      |> Enum.zip(stock_quotes)
      |> Enum.map(fn {weight, %{"volume" => volume}} ->
        weight + volume
      end)
    end)
  end
end
