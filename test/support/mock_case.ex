defmodule HottspotCapital.Test.MockCase do
  use ExUnit.CaseTemplate

  using(_opts) do
    quote do
      alias HottspotCapital.Test.Mocks

      setup do
        Mocks.clear()
        :ok
      end

      setup_all do
        {:ok, _pid} = Mocks.start_link()
        :ok
      end
    end
  end
end
