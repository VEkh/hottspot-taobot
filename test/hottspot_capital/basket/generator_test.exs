defmodule HottspotCapital.Basket.GeneratorTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Basket.Generator
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Factory

  describe ".generate" do
    test "returns [] if no basket is generated" do
      assert Generator.generate("HOTT") == []
    end

    test "returns list of companies with most correlated closing stock prices" do
      {current_year, _, _} = Date.utc_today() |> Date.to_erl()
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

        quotes
        |> Enum.with_index()
        |> Enum.each(fn {close, index} ->
          date = Date.from_erl!({current_year - index, 8, 26})
          create_stock_quote(%{close: close, date: date, symbol: symbol})
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

    test "excludes quotes from quarterly months" do
      {current_year, _, _} = Date.utc_today() |> Date.to_erl()
      quarterly_months = [1, 4, 7, 10]

      companies = [
        %{symbol: "HOTT"},
        %{symbol: "DIS"},
        %{symbol: "FB"},
        %{symbol: "GOOG"},
        %{symbol: "MSFT"}
      ]

      [companies, stub_stock_quotes(), 1..length(companies)]
      |> Enum.zip()
      |> Enum.each(fn {%{symbol: symbol} = company, quotes, company_index} ->
        is_excluded_company = rem(company_index, 2) == 0

        Factory.create_company(company)

        stock_quote_symbols =
          if is_excluded_company do
            ["HOTT", symbol]
          else
            [symbol]
          end

        quotes
        |> Enum.with_index()
        |> Enum.each(fn {close, quote_index} ->
          stock_quote_month =
            if is_excluded_company do
              month_index = rem(quote_index, length(quarterly_months))
              quarterly_months |> Enum.at(month_index)
            else
              8
            end

          date = Date.from_erl!({current_year - quote_index, stock_quote_month, 15})

          stock_quote_symbols
          |> Enum.each(fn stock_quote_symbol ->
            create_stock_quote(%{close: close, date: date, symbol: stock_quote_symbol})
          end)
        end)
      end)

      [symbols, _] = Generator.generate("HOTT") |> parse_basket()
      assert symbols == ["FB", "MSFT"]
    end
  end

  defp create_stock_quote(%{close: close, date: date, symbol: symbol}) do
    %{
      close: close,
      date: date,
      open: close,
      symbol: symbol,
      volume: 100_000
    }
    |> StockQuote.changeset()
    |> StockQuote.upsert()
  end

  defp parse_basket(basket) do
    basket
    |> Enum.reduce([[], []], fn basket_item, [symbols, correlations] ->
      [{symbol, correlation}] = Map.to_list(basket_item)
      [symbols ++ [symbol], correlations ++ [correlation]]
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
      num |> String.to_float() |> Float.round(2)
    end)
    |> Enum.chunk_every(5)
  end
end
