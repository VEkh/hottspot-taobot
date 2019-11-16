defmodule HottspotCapital.Test.DataCase do
  use ExUnit.CaseTemplate

  alias HottspotCapital.Repo

  using(concurrent: true) do
    quote do
      setup do
        :ok = Ecto.Adapters.SQL.Sandbox.mode(Repo, {:shared, self()})
      end
    end
  end

  using(_) do
  end

  setup do
    :ok = Ecto.Adapters.SQL.Sandbox.checkout(HottspotCapital.Repo)
  end
end
