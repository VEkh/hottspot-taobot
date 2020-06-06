defmodule HottspotCapital.MixProject do
  use Mix.Project

  def project do
    [
      app: :hottspot_capital,
      aliases: aliases(),
      deps: deps(),
      elixir: "~> 1.8",
      start_permanent: Mix.env() == :prod,
      version: "0.1.0"
    ]
    |> Keyword.merge(project_config(Mix.env()))
  end

  def application do
    [
      extra_applications: [:logger],
      mod: {HottspotCapital.Application, []}
    ]
  end

  defp aliases() do
    [
      "ecto.migrate": ["ecto.migrate", "ecto.dump"]
    ]
  end

  defp deps do
    [
      {:ecto, "~> 3.1.4"},
      {:ecto_sql, "~> 3.1.2"},
      {:httpoison, "~> 1.6.2"},
      {:jason, "~> 1.1"},
      {:logger_file_backend, git: "https://github.com/vekh/logger_file_backend"},
      {:postgrex, "~> 0.14.0"}
    ]
  end

  defp project_config(:test) do
    [
      elixirc_paths: ["lib", "test/support"]
    ]
  end

  defp project_config(_), do: []
end
