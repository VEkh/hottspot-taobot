defmodule HottspotCapital.Test.Stubs.StockQuoteStubs do
  def group_closes_and_volumes(closes_and_volumes, chunk_size: chunk_size) do
    closes_and_volumes
    |> Enum.map(fn num ->
      magnitude =
        num
        |> String.split(~r/e\+/)
        |> Enum.at(1)
        |> String.to_integer()

      if magnitude <= 2 do
        num |> String.to_float() |> Float.round(2)
      else
        num |> String.to_float() |> Kernel.trunc()
      end
    end)
    |> Enum.chunk_every(chunk_size)
  end
end
