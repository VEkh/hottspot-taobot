defmodule HottspotCapital.Test.Mocks.HTTPoison do
  alias HottspotCapital.Test.Mocks

  def request(
        :get,
        "https://cloud.iexapis.com/stable/stock/" <> rest,
        _body \\ "",
        _headers \\ [],
        _request_options \\ []
      ) do
    case String.split(rest, "/") do
      [_symbol, "chart", range] -> get_historical_stock_quotes(range)
    end
  end

  defp get_historical_stock_quotes(range) do
    mocked_stock_quotes =
      Mocks.get_in([
        HottspotCapital.Test.Mocks.HTTPoison,
        :get_historical_stock_quotes
      ])

    case mocked_stock_quotes do
      nil ->
        body =
          range
          |> Mocks.IexApiClient.get_historical_stock_quotes()
          |> Jason.encode!()

        response = %{body: body, status_code: 200}
        {:ok, response}

      response ->
        response
    end
  end
end
