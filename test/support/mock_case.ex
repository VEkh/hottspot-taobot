defmodule HottspotCapital.Test.MockCase do
  use ExUnit.CaseTemplate
  alias HottspotCapital.Test.DynamicMocks

  setup do
    DynamicMocks.clear()
    :ok
  end

  setup_all do
    {:ok, _pid} = DynamicMocks.start_link()
    :ok
  end
end
