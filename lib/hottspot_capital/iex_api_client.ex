defmodule HottspotCapital.IexApiClient do
  def client(), do: config()[:module]

  def fetch_stock_quote(symbol, attempt \\ 1) do
    response = client().get("/stock/#{symbol}/quote")

    case [response, attempt] do
      [%{"symbol" => _} = resp, _] ->
        resp

      [{:ok, %{status_code: 502}}, current_attempt] when current_attempt < 3 ->
        retry_wait = config()[:request_retry_wait]
        Process.sleep(retry_wait)
        fetch_stock_quote(symbol, attempt + 1)

      [{:ok, %{status_code: 502}}, _] ->
        nil
    end
  end

  def get(path) do
    with {:ok, %{body: body, status_code: 200}} <- request(:get, path),
         {:ok, decoded_body} <- Jason.decode(body) do
      decoded_body
    end
  end

  defp config, do: Application.get_env(:hottspot_capital, :iex_api_client)

  defp request(method, path) do
    %{
      base_url: base_url,
      secret_token: secret_token
    } = config() |> Enum.into(%{})

    headers = [
      {"Accepts", "application/json"},
      {"Content-Type", "application/json"}
    ]

    options = [params: [token: secret_token]]

    %{path: root_path} = base_uri = URI.parse(base_url)

    url =
      base_uri
      |> Map.put(:path, root_path <> path)
      |> URI.to_string()

    HTTPoison.request(method, url, "", headers, options)
  end
end
