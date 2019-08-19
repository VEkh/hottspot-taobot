defmodule HottspotCapital.Test.CalendarCase do
  use ExUnit.CaseTemplate

  alias HottspotCapital.Test.Mocks.Calendar

  using(_opts) do
    quote do
      alias HottspotCapital.Test.Mocks.Calendar
    end
  end

  setup_all do
    {:ok, _pid} = Calendar.start_link()
    :ok
  end
end
