use Mix.Config

config(
  :hottspot_capital,
  :iex_api_client,
  module: HottspotCapital.IexApiClient
)

import_config "#{Mix.env()}*.exs"
