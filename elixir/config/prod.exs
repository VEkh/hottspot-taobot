use Mix.Config

config(
  :hottspot_capital,
  HottspotCapital.Repo,
  database: "hottspot_capital_production"
)

config(
  :hottspot_capital,
  :etrade_api_client,
  base_url: "https://api.etrade.com"
)

