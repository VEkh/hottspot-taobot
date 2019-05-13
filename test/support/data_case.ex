defmodule HottspotCapital.Test.DataCase do
  use ExUnit.CaseTemplate

  setup do
    :ok = Ecto.Adapters.SQL.Sandbox.checkout(HottspotCapital.Repo)
  end
end
