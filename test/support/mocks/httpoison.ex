defmodule HottspotCapital.Test.Mocks.HTTPoison do
  alias HottspotCapital.Test.DynamicMocks
  alias HottspotCapital.Test.Stubs.IexApiStubs

  def request(
        :get,
        "https://cloud.iexapis.com/stable/stock/" <> rest,
        _body \\ "",
        _headers \\ [],
        _request_options \\ []
      ) do
    mocked_response =
      DynamicMocks.get_in([
        HottspotCapital.Test.Mocks.HTTPoison,
        :get_stock
      ])

    case mocked_response do
      nil ->
        [symbol, "quote" <> _ | _] = rest |> String.split("/")

        response = %{
          body: IexApiStubs.stock_quote(symbol),
          status_code: 200
        }

        {:ok, response}

      response ->
        response
    end
  end
end
