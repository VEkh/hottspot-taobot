defmodule HottspotCapital.Test.MockCase do
  use ExUnit.CaseTemplate

  using(_opts) do
    quote do
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
  end
end
