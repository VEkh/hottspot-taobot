defmodule HottspotCapital.IexApiClient do
  alias HottspotCapital.RequestLogger

  defmodule HistoricalStockQuote do
    defstruct close: nil,
              date: nil,
              open: nil,
              volume: nil
  end

  defmodule StockQuote do
    defstruct close: nil,
              company_name: nil,
              date: nil,
              market_cap: nil,
              open: nil,
              symbol: nil,
              volume: nil
  end

  def fetch_historical_stock_quotes(symbol, years: years) when years in [1, 2, 5] do
    case client().get("/stock/#{symbol}/chart/#{years}y") do
      [%{} | _] = historical_stock_quotes ->
        historical_stock_quotes
        |> Enum.map(&parse_historical_stock_quote/1)

      nil ->
        nil
    end
  end

  def fetch_stock_quote(symbol) do
    case client().get("/stock/#{symbol}/quote") do
      %{} = stock_quote -> parse_stock_quote(stock_quote)
      nil -> nil
    end
  end

  def get(path) do
    with {:ok, %{body: body, status_code: 200}} <- request(:get, path),
         {:ok, decoded_body} <- Jason.decode(body) do
      decoded_body
    end
  end

  def client(), do: config()[:module]

  defp config(), do: Application.get_env(:hottspot_capital, :iex_api_client)

  defp parse_historical_stock_quote(%{
         "close" => close,
         "date" => date,
         "open" => open,
         "volume" => volume
       }) do
    %HistoricalStockQuote{
      close: close / 1,
      date: Date.from_iso8601!(date),
      open: open / 1,
      volume: volume
    }
  end

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

  defp request(method, path, options \\ []) do
    %{
      base_url: base_url,
      request_retry_wait: request_retry_wait,
      secret_token: secret_token
    } = config() |> Enum.into(%{})

    http_client = Application.get_env(:hottspot_capital, :http_client)

    %{attempt: attempt} =
      [attempt: 1]
      |> Keyword.merge(options)
      |> Enum.into(%{})

    headers = [
      {"Accepts", "application/json"},
      {"Content-Type", "application/json"}
    ]

    request_options = [params: [token: secret_token]]

    %{path: root_path} = base_uri = URI.parse(base_url)

    url =
      base_uri
      |> Map.put(:path, Path.join(root_path, path))
      |> URI.to_string()

    RequestLogger.log(%HTTPoison.Request{
      headers: headers,
      method: method,
      options: request_options,
      url: url
    })

    response = http_client.request(method, url, "", headers, request_options)

    case [response, attempt] do
      [{:ok, %{status_code: status_code}} = resp, _] when status_code in 200..399 ->
        resp

      [{:ok, %{status_code: 502}}, current_attempt] when current_attempt < 3 ->
        Process.sleep(request_retry_wait)
        request(method, path, attempt: attempt + 1)

      [{:ok, %{status_code: 502}}, _] ->
        nil
    end
  end
end
