use Mix.Config

config(
  :hottspot_capital,
  HottspotCapital.Repo,
  database: "hottspot_capital_development"
)

config(
  :hottspot_capital,
  :iex_api_client,
  base_url: "https://sandbox.iexapis.com/stable"
)
