defmodule HottspotCapital.CompanyTest do
  use HottspotCapital.Test.DataCase

  alias HottspotCapital.Company
  alias HottspotCapital.Test.Factory

  describe ".get_largest" do
    test "gets largest n companies" do
      [
        %{market_cap: 8, symbol: "AMZN"},
        %{market_cap: 7, symbol: "FB"},
        %{market_cap: 6, symbol: "GOOG"},
        %{market_cap: 10, symbol: "HOTT"},
        %{market_cap: 9, symbol: "MSFT"}
      ]
      |> Enum.each(&Factory.create_company/1)

      assert ["HOTT", "MSFT", "AMZN"] =
               Company.get_largest(3)
               |> Enum.map(&Map.get(&1, :symbol))
    end
  end
end
