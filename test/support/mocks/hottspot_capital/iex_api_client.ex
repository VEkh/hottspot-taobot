defmodule HottspotCapital.Test.Mocks.IexApiClient do
  alias HottspotCapital.Test.DynamicMocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  def get("/ref-data/symbols") do
    mocked_symbols =
      DynamicMocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_symbols
      ])

    case mocked_symbols do
      nil -> IexApiStubs.symbols()
      symbols -> symbols
    end
  end

  def get("/stock/" <> rest) do
    case String.split(rest, "/") do
      [_symbol, "chart", range] -> get_historical_stock_quotes(range)
      [symbol, "quote"] -> get_stock_quote(symbol)
    end
  end

  defp get_historical_stock_quotes(range) do
    %{"date" => previous_date} = previous_stock_quote = IexApiStubs.historical_stock_quote()

    earliest_date =
      case Regex.run(~r/(\d+)(\w)/, range) do
        [_, years, "y"] ->
          years_to_subtract = String.to_integer(years)
          {year, month, date} = Date.from_iso8601!(previous_date) |> Date.to_erl()
          Date.from_erl!({year - years_to_subtract, month, date}) |> Date.to_string()

        _ ->
          previous_date
      end

    earliest_stock_quote =
      previous_stock_quote
      |> Map.put("date", earliest_date)

    [earliest_stock_quote, previous_stock_quote]
  end

  defp get_stock_quote(symbol) do
    mocked_stock =
      DynamicMocks.get_in([
        HottspotCapital.Test.Mocks.IexApiClient,
        :get_stock
      ])

    case mocked_stock do
      nil -> IexApiStubs.stock_quote(symbol)
      stock -> stock
    end
  end
end
