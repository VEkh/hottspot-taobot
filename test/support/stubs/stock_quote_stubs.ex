defmodule HottspotCapital.Test.Stubs.StockQuoteStubs do
  def group_closes_and_volumes(closes_and_volumes, days: days) do
    closes_and_volumes
    |> Enum.chunk_every(2)
    |> Enum.map(fn [close, volume] ->
      close = close |> String.to_float() |> Float.round(2)
      volume = volume |> String.to_float() |> Kernel.trunc()
      [close, volume]
    end)
    |> Enum.chunk_every(days)
  end
end
