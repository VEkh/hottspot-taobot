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
  module: HottspotCapital.IexApiClient,
  request_retry_wait: 1000
)

config(:logger, backends: [{LoggerFileBackend, :file_log}])

config(
  :logger,
  :file_log,
  format: "\n\n$dateT$time [$level] $message",
  path: Path.join([File.cwd!(), "log", "#{Mix.env()}.log"])
)

import_config "#{Mix.env()}*.exs"
