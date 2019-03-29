defmodule HottspotCapital.MixProject do
  use Mix.Project

  def project do
    [
      app: :hottspot_capital,
      deps: deps(),
      elixir: "~> 1.8",
      start_permanent: Mix.env() == :prod,
      version: "0.1.0"
    ]
    |> Keyword.merge(project_config(Mix.env()))
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      {:jason, "~> 1.1"},
      {:httpoison, "~> 1.5.1"}
    ]
  end

  defp project_config(:test) do
    [
      elixirc_paths: ["lib", "test/support"]
    ]
  end

  defp project_config(_), do: []
end
