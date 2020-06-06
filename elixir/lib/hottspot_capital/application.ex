defmodule HottspotCapital.Application do
  use Application

  def start(_type, _args) do
    children = [
      {HottspotCapital.Repo, []}
    ]

    options = [
      name: HottspotCapital.Supervisor,
      strategy: :one_for_one
    ]

    Supervisor.start_link(children, options)
  end
end
