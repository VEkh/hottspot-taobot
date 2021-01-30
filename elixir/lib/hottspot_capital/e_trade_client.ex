# NOTE: Untested
defmodule HottspotCapital.ETradeClient do
  alias HottspotCapital.CppClient

  defstruct beta: nil, symbol: nil

  def fetch_quote(symbol) do
    {:ok, quote_json} = CppClient.execute("etrade", ["fetch_quote", symbol])

    quote_json |> Jason.decode!() |> parse_quote
  end

  defp parse_quote(quote_json) do
    %{
      "QuoteResponse" => %{
        "QuoteData" => [
          %{
            "All" => %{"beta" => beta},
            "Product" => %{"symbol" => symbol}
          }
        ]
      }
    } = quote_json

    %__MODULE__{beta: beta, symbol: symbol}
  end
end
