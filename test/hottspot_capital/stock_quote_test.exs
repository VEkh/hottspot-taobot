defmodule HottspotCapital.StockQuoteTest do
  use HottspotCapital.Test.CalendarCase
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.StockQuote
  alias HottspotCapital.Test.Factory

  describe ".missing_data_range" do
    test "returns 5y when quotes have never been imported" do
      assert StockQuote.missing_data_range("HOTT") == "5y"
    end

    test "returns range based on most recent quote date" do
      symbol = "HOTT"
      Factory.create_company(%{symbol: symbol})

      Calendar.set_datetime({{2019, 08, 16}, {0, 0, 0}})

      Factory.create_stock_quote(%{date: ~D[2019-08-13], symbol: symbol})
      assert StockQuote.missing_data_range("HOTT") == "5d"

      Calendar.set_datetime({{2019, 08, 19}, {0, 0, 0}})

      Factory.create_stock_quote(%{date: ~D[2019-08-15], symbol: symbol})
      assert StockQuote.missing_data_range("HOTT") == "20190816?chartByDay=true"

      Factory.create_stock_quote(%{date: ~D[2019-08-16], symbol: symbol})
      assert StockQuote.missing_data_range("HOTT") == :no_missing_data
    end
  end
end
