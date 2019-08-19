defmodule HottspotCapital.Test.Mocks.Calendar do
  use Agent

  def local_time() do
    Agent.get(__MODULE__, fn datetime -> datetime end)
  end

  def set_datetime(datetime = {{_year, _month, _day}, {_hour, _minute, _second}}) do
    Agent.get_and_update(__MODULE__, fn _state -> {datetime, datetime} end)
  end

  def start_link() do
    Agent.start_link(fn -> :calendar.local_time() end, name: __MODULE__)
  end
end
