defmodule HottspotCapital.Basket.GeneratorTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Basket.Generator
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.StockQuoteStubs

  describe ".generate" do
    setup _ do
      {current_year, _, _} = Date.utc_today() |> Date.to_erl()
      [current_year: current_year]
    end

    test "returns [] if no basket is generated" do
      assert Generator.generate("HOTT") == []
    end

    test "returns list of companies with most correlated closing stock prices", %{
      current_year: current_year
    } do
      stubbed_quotes = stubbed_closes_and_volumes()

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

        quotes
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({current_year - index, 8, 26}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      [symbols, correlations] =
        "HOTT"
        |> Generator.generate()
        |> parse_basket()

      assert symbols == ["FB", "GOOG", "MSFT", "DIS"]

      assert Enum.all?(correlations, fn correlation ->
               correlation < 1 && correlation > -1
             end)
    end

    test "accepts date limit" do
      stubbed_quotes = stubbed_closes_and_volumes()
      date_limit = ~D[2017-02-14]

      [
        [
          %{is_within_date_limit: true, symbol: "HOTT"},
          %{is_within_date_limit: false, symbol: "DIS"},
          %{is_within_date_limit: true, symbol: "FB"},
          %{is_within_date_limit: false, symbol: "GOOG"},
          %{is_within_date_limit: false, symbol: "MSFT"}
        ],
        stubbed_quotes
      ]
      |> Enum.zip()
      |> Enum.each(fn {%{is_within_date_limit: is_within_date_limit, symbol: symbol}, quotes} ->
        Factory.create_company(%{symbol: symbol})

        quotes
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          dates =
            case [symbol, is_within_date_limit] do
              ["HOTT", _] ->
                [
                  Date.from_erl!({2017 - index, 8, 26}),
                  Date.from_erl!({2019, 8 - index, 26})
                ]

              [_, true] ->
                [Date.from_erl!({2017 - index, 8, 26})]

              [_, false] ->
                [Date.from_erl!({2019, 8 - index, 26})]
            end

          dates
          |> Enum.each(fn date ->
            Factory.create_stock_quote(%{
              close: close,
              date: date,
              symbol: symbol,
              volume: volume
            })
          end)
        end)
      end)

      [symbols, _] =
        "HOTT"
        |> Generator.generate(date_limit: date_limit)
        |> parse_basket()

      assert symbols == ["FB"]
    end

    test "exclude company from basket if it has no quotes prior to date limit" do
      ["HOTT", "MSFT", "AMZN", "GOOG", "FB", "APPL"]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {symbol, data} ->
        Factory.create_company(%{symbol: symbol})

        data
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({2019, 08, 26 - index}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      assert Generator.generate("HOTT", date_limit: ~D[2019-08-23]) == []
    end

    test "basket company sectors are unique", %{current_year: current_year} do
      [
        %{symbol: "HOTT", sector: "Technology"},
        %{symbol: "DIS", sector: "Entertainment"},
        %{symbol: "GOOG", sector: "Technology"},
        %{symbol: "FB", sector: "Technology"},
        %{symbol: "JPM", sector: "Finance"}
      ]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {%{symbol: symbol} = company, stock_quotes} ->
        Factory.create_company(company)

        stock_quotes
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({current_year - index, 8, 26}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      [symbols, _] =
        "HOTT"
        |> Generator.generate()
        |> parse_basket()

      assert symbols == ["DIS", "GOOG", "JPM"]
    end

    test "excludes companies of the same name", %{current_year: current_year} do
      [
        %{symbol: "HOTT", name: "Hottspot, Inc"},
        %{symbol: "HOTT.A", name: "Hottspot, Inc"},
        %{symbol: "DIS", name: "Disney"},
        %{symbol: "GOOG", name: "Alphabet, Inc"},
        %{symbol: "JPM", name: "JPMorgan Chase & Co."}
      ]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {%{symbol: symbol} = company, stock_quotes} ->
        Factory.create_company(company)

        stock_quotes
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({current_year - index, 8, 26}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      [symbols, _] =
        "HOTT"
        |> Generator.generate()
        |> parse_basket()

      assert symbols == ["DIS", "GOOG", "JPM"]
    end
  end

  defp parse_basket(basket) do
    basket
    |> Enum.reduce([[], []], fn basket_item, [symbols, correlations] ->
      [{symbol, correlation}] = Map.to_list(basket_item)
      [symbols ++ [symbol], correlations ++ [correlation]]
    end)
  end

  # Sorted in descending order of correlation to the first row
  defp stubbed_closes_and_volumes() do
    ~w[
      248.647   1.000e+5
      143.316   1.000e+5
      241.085   1.000e+5
      283.310   1.000e+5
      988.603   1.000e+5

      555.341   1.000e+5
      418.366   1.000e+5
      216.946   1.000e+5
      707.539   1.000e+5
      954.135   1.000e+5

      763.177   1.000e+5
      475.570   1.000e+5
      703.831   1.000e+5
      259.764   1.000e+5
      830.914   1.000e+5

      554.855   1.000e+5
      254.909   1.000e+5
      459.352   1.000e+5
      229.249   1.000e+5
      291.113   1.000e+5

      118.369   1.000e+5
      928.406   1.000e+5
      367.049   1.000e+5
      370.311   1.000e+5
       58.182   1.000e+5
    ]
    |> StockQuoteStubs.group_closes_and_volumes(days: 5)
  end
end
