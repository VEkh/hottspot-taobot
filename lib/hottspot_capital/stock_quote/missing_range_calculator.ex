defmodule HottspotCapital.StockQuote.MissingRangeCalculator do
  def calculate(nil), do: "5y"

  def calculate(date) do
    weekdays_since_last_quote =
      calendar().local_time()
      |> elem(0)
      |> Date.from_erl!()
      |> weekday_difference(date)

    case weekdays_since_last_quote do
      2 -> previous_weekday_range()
      weekdays when weekdays in 0..1 -> :no_missing_data
      weekdays when weekdays in 3..5 -> "5d"
      weekdays when weekdays in 6..23 -> "1m"
      weekdays when weekdays in 24..66 -> "3m"
      weekdays when weekdays in 67..131 -> "6m"
      weekdays when weekdays in 131..262 -> "1y"
      weekdays when weekdays in 263..523 -> "2y"
      weekdays when weekdays in 524..1305 -> "5y"
    end
  end

  defp calendar(), do: Application.get_env(:hottspot_capital, :calendar)

  defp previous_weekday_range() do
    current_date =
      calendar().local_time()
      |> elem(0)
      |> Date.from_erl!()

    previous_weekdate =
      current_date
      |> Date.range(Date.add(current_date, -7))
      |> Enum.filter(fn date ->
        Date.day_of_week(date) in 1..5 && date != current_date
      end)
      |> List.first()
      |> Date.to_iso8601(:basic)

    %URI{
      path: Path.join(["date", previous_weekdate]),
      query: URI.encode_query(chartByDay: true)
    }
    |> URI.to_string()
  end

  defp weekday_difference(date_1, date_2) do
    date_1
    |> Date.range(date_2)
    |> Enum.filter(fn date ->
      Date.day_of_week(date) in 1..5 && date != date_1
    end)
    |> length()
  end
end
