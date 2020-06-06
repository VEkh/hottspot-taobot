use Mix.Config

config(
  :hottspot_capital,
  HottspotCapital.Repo,
  database: "hottspot_capital_test",
  pool: Ecto.Adapters.SQL.Sandbox
)

config(
  :hottspot_capital,
  calendar: HottspotCapital.Test.Mocks.Calendar,
  http_client: HottspotCapital.Test.Mocks.HTTPoison
)

config(
  :hottspot_capital,
  :iex_api_client,
  module: HottspotCapital.Test.Mocks.IexApiClient,
  secret_token: "secret"
)
