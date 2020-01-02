defmodule HottspotCapital.Test.Mocks.IexApiClient do
  alias HottspotCapital.Test.Mocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  def get("/ref-data/symbols") do
    Mocks.get_in([
      HottspotCapital.Test.Mocks.IexApiClient,
      :get_symbols
    ]) || IexApiStubs.symbols()
  end

  def get("/stock/" <> rest) do
    case String.split(rest, "/") do
      [_symbol, "chart", range] -> get_historical_stock_quotes(range)
      [_symbol, "stats", stat] -> get_company_stat(stat)
      [symbol, "company"] -> get_company(symbol)
      [symbol, "quote" <> _ | _] -> get_stock_quote(symbol)
    end
  end

  def get_historical_stock_quotes(range) do
    %{"date" => previous_date} = previous_stock_quote = IexApiStubs.historical_stock_quote()

    [_, year_range, "y"] = Regex.run(~r/(\d+)(\w)/, range)

    {previous_year, previous_month, previous_day} =
      previous_date
      |> Date.from_iso8601!()
      |> Date.to_erl()

    earliest_year = previous_year - String.to_integer(year_range)

    earliest_year..previous_year
    |> Enum.map(fn year ->
      date =
        {year, previous_month, previous_day}
        |> Date.from_erl!()
        |> Date.to_iso8601()

      Map.put(previous_stock_quote, "date", date)
    end)
  end

  defp get_company(symbol) do
    Mocks.get_in([
      HottspotCapital.Test.Mocks.IexApiClient,
      :get_company
    ]) || IexApiStubs.company(symbol)
  end

  defp get_company_stat(stat) do
    mocked_stats =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_company_stats
      ]) || IexApiStubs.company_stats()

    Map.get(mocked_stats, stat)
  end

  defp get_stock_quote(symbol) do
    Mocks.get_in([
      HottspotCapital.Test.Mocks.IexApiClient,
      :get_stock
    ]) || IexApiStubs.stock_quote(symbol)
  end
end
