use Mix.Config

config(
  :hottspot_capital,
  HottspotCapital.Repo,
  database: "hottspot_capital",
  hostname: "localhost",
  password: "password",
  username: "hottspot_capital"
)

config(
  :hottspot_capital,
  :etrade_api_client,
  consumer_key: "key",
  consumer_secret: "secret"
)

config(
  :hottspot_capital,
  :iex_api_client,
  base_url: "https://sandbox.iexapis.com/stable",
  secret_token: "SECRET_TOKEN"
)
