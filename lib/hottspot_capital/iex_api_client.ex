defmodule HottspotCapital.IexApiClient do
  defmodule StockQuote do
    defstruct close: nil,
              company_name: nil,
              date: nil,
              market_cap: nil,
              open: nil,
              symbol: nil,
              volume: nil
  end

  def fetch_stock_quote(symbol, attempt \\ 1) do
    response = client().get("/stock/#{symbol}/quote")

    case [response, attempt] do
      [%{"symbol" => _} = resp, _] ->
        parse_stock_quote(resp)

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

  def client(), do: config()[:module]

  defp config, do: Application.get_env(:hottspot_capital, :iex_api_client)

  defp parse_stock_quote(%{
         "close" => close,
         "closeTime" => close_date_epoch,
         "companyName" => company_name,
         "latestVolume" => volume,
         "marketCap" => market_cap,
         "open" => open,
         "symbol" => symbol
       })
       when nil not in [close, close_date_epoch, open] do
    close_date =
      close_date_epoch
      |> DateTime.from_unix!(:millisecond)
      |> DateTime.to_date()

    %StockQuote{
      close: close / 1,
      company_name: company_name,
      date: close_date,
      market_cap: market_cap,
      open: open / 1,
      symbol: symbol,
      volume: volume
    }
  end

  defp parse_stock_quote(_), do: nil

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
