defmodule HottspotCapital.IexApiClient do
  def get(path) do
    with {:ok, %{body: body, status_code: 200}} <- request(:get, path),
         {:ok, decoded_body} <- parse_response_body(body) do
      decoded_body
    else
      _ -> :error
    end
  end

  defp parse_response_body(body), do: Jason.decode(body)

  defp request(method, path) do
    %{
      base_url: base_url,
      secret_token: secret_token
    } =
      Application.get_env(:hottspot_capital, :iex_api_client)
      |> Enum.into(%{})

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
