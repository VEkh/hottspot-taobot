defmodule HottspotCapital.IexApiClient do
  alias HottspotCapital.RequestLogger

  defmodule Company do
    defstruct name: nil, sector: nil, symbol: nil
  end

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

  def fetch_company(symbol) do
    case client().get("/stock/#{symbol}/company") do
      %{} = company -> parse_company(company)
      nil -> nil
    end
  end

  def fetch_historical_stock_quotes(range: :no_missing_data, symbol: _), do: []

  def fetch_historical_stock_quotes(range: range, symbol: symbol) do
    client = client()

    "/stock/#{symbol}/chart/#{range}"
    |> client.get()
    |> Enum.map(&parse_historical_stock_quote/1)
  end

  def fetch_stock_quote(symbol) do
    case client().get("/stock/#{symbol}/quote") do
      %{} = stock_quote -> parse_stock_quote(stock_quote)
      nil -> nil
    end
  end

  def fetch_stock_beta(symbol) do
    client().get("/stock/#{symbol}/stats/beta")
  end

  def get(path) do
    with {:ok, %{body: body, status_code: 200}} <- request(:get, path),
         {:ok, decoded_body} <- Jason.decode(body) do
      decoded_body
    else
      {:ok, nil} -> nil
      resp -> resp
    end
  end

  def client(), do: config()[:module]

  defp config(), do: Application.get_env(:hottspot_capital, :iex_api_client)

  defp parse_company(%{
         "companyName" => <<_::binary>> = name,
         "sector" => <<_::binary>> = sector,
         "symbol" => <<_::binary>> = symbol
       }) do
    %Company{
      name: name,
      sector: sector,
      symbol: symbol
    }
  end

  defp parse_company(_), do: nil

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

  defp parse_response(response) do
    case response do
      {:ok, %{status_code: status_code}} when status_code in 200..399 -> response
      {:ok, %{status_code: 404}} -> {:ok, nil}
      {:ok, %{status_code: 502}} -> {:retry, nil}
      {:error, %{reason: reason}} when reason in [:closed, :timeout] -> {:retry, nil}
    end
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
    options = [attempt: 1] |> Keyword.merge(options)

    client_request_options = [params: [token: secret_token]]

    request_headers = [
      {"Accepts", "application/json"},
      {"Content-Type", "application/json"}
    ]

    url = to_request_url(base_url: base_url, path: path)

    RequestLogger.log(%HTTPoison.Request{
      headers: request_headers,
      method: method,
      options: client_request_options,
      url: url
    })

    response =
      http_client.request(method, url, "", request_headers, client_request_options)
      |> parse_response()

    case response do
      {:ok, _} ->
        response

      {:retry, resp} ->
        case Keyword.get(options, :attempt) do
          attempt when attempt < 3 ->
            Process.sleep(request_retry_wait)
            retry_options = Keyword.put(options, :attempt, attempt + 1)
            request(method, path, retry_options)

          _ ->
            {:ok, resp}
        end
    end
  end

  defp to_request_url(base_url: base_url, path: path) do
    %{path: root_path} = base_uri = URI.parse(base_url)

    base_uri
    |> Map.put(:path, Path.join(root_path, path))
    |> URI.to_string()
  end
end
