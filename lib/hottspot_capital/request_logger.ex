defmodule HottspotCapital.RequestLogger do
  require Logger

  def log(%HTTPoison.Request{
        headers: headers,
        method: method,
        options: options,
        params: params,
        url: url
      }) do
    headers_string = headers_to_string(headers)
    method = String.upcase("#{method}")
    query = params_to_query(params: params, options: options)
    url = URI.parse(url) |> Map.put(:query, query) |> URI.to_string()

    Logger.info("curl -X#{method} #{headers_string} #{url}")
  end

  defp headers_to_string(headers) when is_list(headers) do
    headers
    |> Enum.map(fn {key, value} -> "-H \"#{key}: #{value}\"" end)
    |> Enum.join(" ")
  end

  defp params_to_query(
         params: %{} = params,
         options: options
       )
       when is_list(options) do
    query =
      options
      |> Keyword.get(:params, [])
      |> Enum.into(params)
      |> URI.encode_query()

    case query do
      "" -> nil
      query -> query
    end
  end
end
