defmodule HottspotCapital.StockQuote.MissingRangeCalculatorTest do
  use HottspotCapital.Test.CalendarCase

  alias HottspotCapital.StockQuote.MissingRangeCalculator

  describe ".calculate" do
    test "returns 5y when last quote is nil" do
      assert MissingRangeCalculator.calculate(nil) == "5y"
    end

    test "returns :no_missing_data if last quote was one weekday ago" do
      Calendar.set_datetime({{2019, 08, 19}, {0, 0, 0}})

      assert MissingRangeCalculator.calculate(~D[2019-08-16]) ==
               :no_missing_data
    end

    test "returns :no_missing_data if last quote was less than one weekday ago" do
      Calendar.set_datetime({{2019, 08, 19}, {0, 0, 0}})

      [
        ~D[2019-08-17],
        ~D[2019-08-18],
        ~D[2019-08-19]
      ]
      |> Enum.each(fn date ->
        assert MissingRangeCalculator.calculate(date) == :no_missing_data
      end)
    end

    test "returns single date when last quote was last Thursday" do
      [
        # Monday
        {2019, 08, 19},
        # Sunday
        {2019, 08, 18},
        # Saturday
        {2019, 08, 17}
      ]
      |> Enum.each(fn date ->
        Calendar.set_datetime({date, {0, 0, 0}})

        assert MissingRangeCalculator.calculate(~D[2019-08-15]) ==
                 "20190816?chartByDay=true"
      end)
    end

    test "returns single date when last quote was two weekdays earlier that week" do
      # Wednesday
      Calendar.set_datetime({{2019, 08, 21}, {0, 0, 0}})

      assert MissingRangeCalculator.calculate(~D[2019-08-19]) ==
               "20190820?chartByDay=true"

      # Friday
      Calendar.set_datetime({{2019, 08, 23}, {0, 0, 0}})

      assert MissingRangeCalculator.calculate(~D[2019-08-21]) ==
               "20190822?chartByDay=true"
    end

    test "returns 5d when last quote was 3-5 weekdays ago" do
      [
        # Monday
        {2019, 08, 19},
        # Sunday
        {2019, 08, 18},
        # Saturday
        {2019, 08, 17}
      ]
      |> Enum.each(fn date ->
        Calendar.set_datetime({date, {0, 0, 0}})

        [~D[2019-08-14], ~D[2019-08-13], ~D[2019-08-12]]
        |> Enum.each(fn last_quote_date ->
          assert MissingRangeCalculator.calculate(last_quote_date) == "5d"
        end)
      end)

      # Friday
      Calendar.set_datetime({{2019, 08, 16}, {0, 0, 0}})

      [~D[2019-08-13], ~D[2019-08-12], ~D[2019-08-09]]
      |> Enum.each(fn last_quote_date ->
        assert MissingRangeCalculator.calculate(last_quote_date) == "5d"
      end)
    end

    test "returns 1m when last quote was 6-23 weekdays ago" do
      [
        {{2019, 10, 07}, {2019, 09, 08}},
        {{2019, 11, 04}, {2019, 10, 18}},
        {{2019, 12, 01}, {2019, 11, 10}}
      ]
      |> assert_correct_range_calculation("1m")
    end

    test "returns 3m when last quote was 24-66 weekdays ago" do
      [
        {{2019, 10, 07}, {2019, 08, 28}},
        {{2019, 11, 09}, {2019, 09, 11}},
        {{2019, 12, 01}, {2019, 09, 01}}
      ]
      |> assert_correct_range_calculation("3m")
    end

    test "returns 6m when last quote was 67-131 weekdays ago" do
      [
        {{2019, 01, 15}, {2018, 09, 30}},
        {{2019, 10, 04}, {2019, 07, 01}},
        {{2019, 12, 01}, {2019, 06, 01}}
      ]
      |> assert_correct_range_calculation("6m")
    end

    test "returns 1y when last quote was 132-262 weekdays ago" do
      [
        {{2019, 03, 15}, {2018, 07, 30}},
        {{2019, 10, 04}, {2019, 04, 01}},
        {{2019, 12, 01}, {2018, 12, 01}}
      ]
      |> assert_correct_range_calculation("1y")
    end

    test "returns 2y when last quote was 263-523 weekdays ago" do
      [
        {{2019, 03, 15}, {2017, 12, 25}},
        {{2019, 10, 04}, {2018, 04, 01}},
        {{2019, 12, 01}, {2017, 12, 01}}
      ]
      |> assert_correct_range_calculation("2y")
    end

    test "returns 5y when last quote was 524-1285 weekdays ago" do
      [
        {{2019, 03, 15}, {2015, 12, 25}},
        {{2019, 10, 04}, {2016, 04, 01}},
        {{2019, 12, 01}, {2014, 12, 01}}
      ]
      |> assert_correct_range_calculation("5y")
    end

    defp assert_correct_range_calculation(ranges, assertion) do
      ranges
      |> Enum.each(fn {current_date, last_quote_date} ->
        Calendar.set_datetime({current_date, {0, 0, 0}})

        assert last_quote_date
               |> Date.from_erl!()
               |> MissingRangeCalculator.calculate() == assertion
      end)
    end
  end
end
