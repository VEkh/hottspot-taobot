defmodule HottspotCapital.Test.Stubs.IexApiStubs do
  def base_symbol(symbol) do
    symbols()
    |> hd
    |> Map.put("symbol", String.upcase(symbol))
  end

  def historical_stock_quote() do
    Path.join([File.cwd!(), "test", "support", "fixtures", "historical_stock_quote.json"])
    |> File.read!()
    |> Jason.decode!()
  end

  def stock_quote("NIL_CLOSE" = symbol) do
    symbol
    |> base_stock_quote()
    |> Map.merge(%{"close" => nil})
  end

  def stock_quote("NIL_OPEN" = symbol) do
    symbol
    |> base_stock_quote()
    |> Map.merge(%{"open" => nil})
  end

  def stock_quote(symbol) do
    symbol
    |> base_stock_quote()
    |> Map.merge(%{
      "marketCap" => (:rand.uniform() * :math.pow(10, 12)) |> trunc()
    })
  end

  def symbols() do
    Path.join([File.cwd!(), "test", "support", "fixtures", "symbols.json"])
    |> File.read!()
    |> Jason.decode!()
  end

  defp base_stock_quote(symbol) do
    Path.join([File.cwd!(), "test", "support", "fixtures", "stock_quote.json"])
    |> File.read!()
    |> Jason.decode!()
    |> Map.put("symbol", String.upcase(symbol))
  end
end
