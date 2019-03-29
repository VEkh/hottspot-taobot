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
    [symbol, "quote" <> _ | _] = rest |> String.split("/")

    IexApiStubs.stock_quote(symbol)
  end
end
