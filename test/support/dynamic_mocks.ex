defmodule HottspotCapital.Test.DynamicMocks do
  use Agent

  alias HottspotCapital.Utils

  @init_state %{}

  def clear() do
    Agent.update(__MODULE__, fn _ -> @init_state end)
  end

  def get(key) do
    Agent.get(__MODULE__, fn state -> state[key] end)
  end

  def get_in(keys) do
    Agent.get(__MODULE__, fn state -> get_in(state, keys) end)
  end

  def start_link(init_state \\ @init_state) do
    Agent.start_link(fn -> init_state end, name: __MODULE__)
  end

  def update(%{function: function, module: module, value: value}) do
    Agent.update(
      __MODULE__,
      fn current_state ->
        Utils.update_in_and_build(current_state, [module, function, value])
      end
    )
  end
end
