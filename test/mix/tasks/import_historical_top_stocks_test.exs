defmodule Mix.Tasks.ImportHistoricalTopStocksTest do
  use HottspotCapital.Test.DataCase
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.Repo
  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Factory
  alias Mix.Tasks.ImportHistoricalTopStocks

  test "imports historical stocks from top n companies (default options)" do
    [
      %{market_cap: 8, symbol: "AMZN"},
      %{market_cap: 7, symbol: "FB"},
      %{market_cap: 6, symbol: "GOOG"},
      %{market_cap: 10, symbol: "HOTT"},
      %{market_cap: 9, symbol: "MSFT"}
    ]
    |> Enum.each(&Factory.create_company/1)

    ImportHistoricalTopStocks.run([])

    assert %{
             "AMZN" => [2013, 2014, 2015, 2016, 2017, 2018],
             "FB" => [2013, 2014, 2015, 2016, 2017, 2018],
             "GOOG" => [2013, 2014, 2015, 2016, 2017, 2018],
             "HOTT" => [2013, 2014, 2015, 2016, 2017, 2018],
             "MSFT" => [2013, 2014, 2015, 2016, 2017, 2018]
           } = get_imported_quotes()
  end

  test "accepts companies_limit argument" do
    [
      %{market_cap: 8, symbol: "AMZN"},
      %{market_cap: 7, symbol: "FB"},
      %{market_cap: 6, symbol: "GOOG"},
      %{market_cap: 10, symbol: "HOTT"},
      %{market_cap: 9, symbol: "MSFT"}
    ]
    |> Enum.each(&Factory.create_company/1)

    ImportHistoricalTopStocks.run(["--companies_limit=3"])

    assert %{
             "AMZN" => [2013, 2014, 2015, 2016, 2017, 2018],
             "HOTT" => [2013, 2014, 2015, 2016, 2017, 2018],
             "MSFT" => [2013, 2014, 2015, 2016, 2017, 2018]
           } = get_imported_quotes()
  end

  defp get_imported_quotes() do
    StockQuote
    |> Repo.all()
    |> Enum.reduce(
      %{},
      fn %{date: date, symbol: symbol}, acc ->
        {year, _, _} = Date.to_erl(date)

        years =
          (acc[symbol] || [])
          |> List.insert_at(-1, year)
          |> Enum.uniq()
          |> Enum.sort(fn a, b -> a < b end)

        Map.put(acc, symbol, years)
      end
    )
  end
end
