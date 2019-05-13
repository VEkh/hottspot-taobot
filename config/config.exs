use Mix.Config

config(
  :hottspot_capital,
  HottspotCapital.Repo,
  hostname: "localhost",
  username: "hottspot_capital"
)

config(
  :hottspot_capital,
  :ecto_repos,
  [HottspotCapital.Repo]
)

config(
  :hottspot_capital,
  :iex_api_client,
  module: HottspotCapital.IexApiClient
)

import_config "#{Mix.env()}*.exs"
