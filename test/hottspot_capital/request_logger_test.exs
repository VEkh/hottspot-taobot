defmodule HottspotCapital.Test.RequestLoggerTest do
  use ExUnit.Case

  alias HottspotCapital.RequestLogger

  test "successfully logs GET request with params" do
    :ok =
      RequestLogger.log(%HTTPoison.Request{
        headers: [
          {"Accepts", "application/json"},
          {"Content-Type", "application/json"}
        ],
        method: :get,
        options: [params: [token: "secret"]],
        params: %{version: "3"},
        url: "https://hottspot.co"
      })

    [_ | [curl_request]] = String.split(read_log_last_line(), "[info] ")

    assert curl_request ==
             "curl -XGET -H \"Accepts: application/json\" -H \"Content-Type: application/json\" https://hottspot.co?token=secret&version=3"
  end

  defp read_log_last_line do
    test_log_path = Path.join([File.cwd!(), "log", "#{Mix.env()}.log"])
    File.stream!(test_log_path) |> Enum.at(-1)
  end
end
