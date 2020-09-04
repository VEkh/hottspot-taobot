defmodule HottspotCapital.Oauth do
  @signable_params ~w[
    callback
    consumer_key
    nonce
    signature
    signature_method
    timestamp
  ]a

  defstruct callback: nil,
            consumer_key: nil,
            consumer_secret: nil,
            nonce: nil,
            request: [method: nil, url: nil],
            signature: nil,
            signature_method: nil,
            timestamp: nil,
            token_secret: nil

  defdelegate fetch(map, keys), to: Map

  def build_request_header(args) do
    state = build_state(args)

    params =
      for param <- @signable_params, !is_nil(state[param]) do
        value = URI.encode("#{state[param]}")
        ~s[oauth_#{param}="#{value}"]
      end

    [~s[Authorization: OAuth realm=""]]
    |> Kernel.++(params)
    |> Enum.join(", ")
  end

  defp assign_nonce(%__MODULE__{timestamp: timestamp} = state) do
    nonce =
      :crypto.hash(:sha256, "#{timestamp}")
      |> Base.encode16()

    %{state | nonce: nonce}
  end

  defp assign_signature(%__MODULE__{} = state) do
    signing_key = "#{state[:consumer_secret]}&#{state[:token_secret]}"
    base_signature_string = build_base_signature_string(state)

    signature =
      :crypto.hmac(:sha, signing_key, base_signature_string)
      |> Base.encode64()

    %{state | signature: signature}
  end

  defp build_base_signature_string(%__MODULE__{} = state) do
    %{request: %{method: method, url: url}} = state

    encoded_params =
      for param <- @signable_params, !is_nil(state[param]) do
        encoded_value = URI.encode("#{state[param]}")
        "oauth_#{param}=#{encoded_value}"
      end
      |> Enum.join("&")

    [method, URI.encode(url), URI.encode(encoded_params)]
    |> Enum.join("&")
  end

  defp build_state(args) do
    %__MODULE__{
      callback: "oob",
      consumer_key: System.get_env("OAUTH_CONSUMER_KEY"),
      consumer_secret: System.get_env("OAUTH_CONSUMER_SECRET"),
      signature_method: "HMAC-SHA1",
      timestamp: DateTime.utc_now() |> DateTime.to_unix()
    }
    |> struct(args)
    |> assign_nonce()
    |> assign_signature()
  end
end
