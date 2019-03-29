use Mix.Config

config(
  :hottspot_capital,
  :iex_api_client,
  module: HottspotCapital.Test.Mocks.IexApiClient
)
