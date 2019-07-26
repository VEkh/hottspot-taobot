defmodule HottspotCapital.BasketGeneratorTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.BasketGenerator
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Factory

  describe ".generate" do
    test "returns list of companies with most correlated closing stock prices" do
      stubbed_quotes = stub_stock_quotes()

      [
        {%{symbol: "DIS"}, 5},
        {%{symbol: "FB"}, 2},
        {%{symbol: "GOOG"}, 3},
        {%{symbol: "HOTT"}, 1},
        {%{symbol: "MSFT"}, 4}
      ]
      |> Enum.each(fn {%{symbol: symbol} = company, rank} ->
        Factory.create_company(company)
        quotes = Enum.at(stubbed_quotes, rank - 1)
        create_historical_quotes(quotes: quotes, symbol: symbol)
      end)

      [symbols, correlations] =
        BasketGenerator.generate("HOTT")
        |> Enum.reduce([[], []], fn basket_item, [symbols, correlations] ->
          [{symbol, correlation}] = Map.to_list(basket_item)
          [symbols ++ [symbol], correlations ++ [correlation]]
        end)

      assert symbols == ["FB", "GOOG", "MSFT", "DIS"]

      assert Enum.all?(correlations, fn correlation ->
               correlation < 1 && correlation > -1
             end)
    end
  end

  defp create_historical_quotes(quotes: quotes, symbol: symbol) do
    {current_year, current_month, current_day} = Date.utc_today() |> Date.to_erl()

    quotes
    |> Enum.with_index()
    |> Enum.each(fn {close_price, index} ->
      date = Date.from_erl!({current_year - index, current_month, current_day})

      %{
        close: close_price,
        date: date,
        open: close_price,
        symbol: symbol,
        volume: 100_000
      }
      |> StockQuote.changeset()
      |> StockQuote.upsert()
    end)
  end

  # Sorted in descending order of correlation to the first row
  defp stub_stock_quotes() do
    ~w[
      248.647   143.316   241.085   283.310   988.603
      555.341   418.366   216.946   707.539   954.135
      763.177   475.570   703.831   259.764   830.914
      554.855   254.909   459.352   229.249   291.113
      118.369   928.406   367.049   370.311    58.182
    ]
    |> Enum.map(fn num ->
      num
      |> String.to_float()
      |> Float.round(2)
    end)
    |> Enum.chunk_every(5)
  end
end
