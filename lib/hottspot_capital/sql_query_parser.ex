defmodule HottspotCapital.SQLQueryParser do
  def named_to_ordered_params(query, params) do
    {ordered_params, modified_query} =
      params
      |> Enum.with_index(1)
      |> Enum.map_reduce(query, fn {{key, value}, index}, acc ->
        acc = String.replace(acc, "$#{key}", "$#{index}", global: true)
        {value, acc}
      end)

    {modified_query, ordered_params}
  end
end
