defmodule HottspotCapital.Test.Stubs.IexApiStubs do
  def base_symbol(symbol) do
    symbols()
    |> hd
    |> Map.put("symbol", String.upcase(symbol))
  end

  def company(symbol) do
    Path.join([File.cwd!(), "test", "support", "fixtures", "company.json"])
    |> File.read!()
    |> Jason.decode!()
    |> Map.put("symbol", String.upcase(symbol))
  end

  def company_stats() do
    Path.join([File.cwd!(), "test", "support", "fixtures", "company_stats.json"])
    |> File.read!()
    |> Jason.decode!()
    |> Map.put(
      "marketcap",
      (:rand.uniform() * :math.pow(10, 12)) |> trunc()
    )
  end

  def historical_stock_quote() do
    Path.join([File.cwd!(), "test", "support", "fixtures", "historical_stock_quote.json"])
    |> File.read!()
    |> Jason.decode!()
  end

  def symbols() do
    Path.join([File.cwd!(), "test", "support", "fixtures", "symbols.json"])
    |> File.read!()
    |> Jason.decode!()
  end
end
