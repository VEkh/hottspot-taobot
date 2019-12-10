defmodule HottspotCapital.Basket.Movement.Sum do
  alias HottspotCapital.Basket.Generator
  alias HottspotCapital.Repo
  alias HottspotCapital.SQLQueryParser
  alias HottspotCapital.Utils

  defstruct basket_movement: nil,
            reference: %{
              last_two_closes: [],
              movement: nil,
              symbol: nil
            }

  defdelegate fetch(map, keys), to: Map

  def calculate(symbol, options \\ []) do
    {reference, basket} = get_last_two_stock_quotes(symbol, options)

    case Map.keys(basket) do
      [] ->
        {:error, "Failed to get last two quotes for #{symbol}"}

      _ ->
        %__MODULE__{
          basket_movement: calculate_basket_movement(basket),
          reference: reference_with_movement(reference)
        }
    end
  end

  defp calculate_basket_movement(basket) do
    # Wrong, but accuracy is 0.6568933250155957
    # [to_sum, from_sum] =
    #   basket
    #   |> Enum.reduce(
    #     [0, 0],
    #     fn
    #       {_symbol, quotes}, [from_sum, to_sum] ->
    #         [%{"close" => to}, %{"close" => from}] = quotes
    #         [from_sum + from, to_sum + to]
    #     end
    #   )

    [from_sum, to_sum] =
      basket
      |> Enum.reduce(
        [0, 0],
        fn
          {_symbol, quotes}, [from_sum, to_sum] ->
            [%{"close" => to}, %{"close" => from}] = quotes
            [from_sum + from, to_sum + to]
        end
      )

    movement(from: from_sum, to: to_sum)
  end

  defp get_last_two_stock_quotes(symbol, options) do
    %{date_limit: date_limit} =
      options
      |> Keyword.put(:symbol, symbol)
      |> Generator.merge_options()

    previous_weekdate = Utils.previous_weekdate(date_limit)

    {query, params} =
      """
      SELECT last_two_quotes.symbol, last_two_quotes.quotes

      FROM (
        SELECT basket_query.basket_item_symbol AS symbol
        FROM #{Generator.basket_query()} AS basket_query
        UNION
        SELECT $symbol AS symbol
      ) AS reference_and_basket

      JOIN LATERAL (
        SELECT
          symbol,
          ARRAY_AGG(
            JSON_BUILD_OBJECT(
              'date', date,
              'close', close,
              'volume', volume
            )
            ORDER BY date DESC
          ) AS quotes
        FROM stock_quotes
        WHERE symbol = reference_and_basket.symbol
          AND date IN ($date_limit, $previous_weekdate)
        GROUP BY symbol
        HAVING count(close) = 2
      ) AS last_two_quotes
        ON last_two_quotes.symbol = reference_and_basket.symbol
      """
      |> SQLQueryParser.named_to_ordered_params(
        date_limit: date_limit,
        previous_weekdate: previous_weekdate,
        symbol: symbol
      )

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
          last_two_closes: closes,
          movement: movement(from: penultimate_close, to: last_close),
          symbol: symbol
        }
      )
    end)
  end
end
