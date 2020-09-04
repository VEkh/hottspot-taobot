defmodule HottspotCapital.OauthTest do
  use ExUnit.Case

  alias HottspotCapital.Oauth

  describe ".build_request_header" do
    test "accurately builds a request header" do
      # TODO: Read this from get_env(:etrade_api_client, :consumer_key) (with_env)
      System.put_env([
        {"OAUTH_CONSUMER_KEY", "12345"},
        {"OAUTH_CONSUMER_SECRET", "abcde"}
      ])

      subject =
        Oauth.build_request_header(%{
          request: %{
            method: "GET",
            url: "https://example.com/ouath/request_token"
          }
        })

      captures =
        [
          ~s[Authorization: OAuth realm=""],
          ~s[oauth_callback="(?<callback>.+)"],
          ~s[oauth_consumer_key="(?<consumer_key>.+)"],
          ~s[oauth_nonce="(?<nonce>.+)"],
          ~s[oauth_signature="(?<signature>.+)"],
          ~s[oauth_signature_method="(?<signature_method>.+)"],
          ~s[oauth_timestamp="(?<timestamp>.+)"]
        ]
        |> Enum.join(", ")
        |> Regex.compile!()
        |> Regex.named_captures(subject)

      assert %{
               "callback" => "oob",
               "consumer_key" => "12345",
               "nonce" => nonce,
               "signature" => signature,
               "signature_method" => "HMAC-SHA1",
               "timestamp" => timestamp
             } = captures

      assert {:ok, %DateTime{}} =
               timestamp
               |> String.to_integer()
               |> DateTime.from_unix()

      assert {:ok, nonce} = Base.decode16(nonce)
      assert is_binary(nonce)
      assert {:ok, signature} = signature |> URI.decode() |> Base.decode64()
      assert is_binary(signature)
    end
  end
end
