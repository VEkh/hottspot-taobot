defmodule HottspotCapital.Utils do
  def update_in_and_build(map, list, update_path \\ [])
  def update_in_and_build(map, [], _update_path), do: map
  def update_in_and_build(map, [_ | []], _update_path), do: map

  def update_in_and_build(map, [head | [tail | []]], update_path) do
    update_path = update_path ++ [head]
    put_in(map, update_path, tail)
  end

  def update_in_and_build(map, [head | tail], update_path) do
    update_path = update_path ++ [head]

    map =
      update_in(map, update_path, fn
        %{} = old_value -> old_value
        _ -> %{}
      end)

    update_in_and_build(map, tail, update_path)
  end
end
