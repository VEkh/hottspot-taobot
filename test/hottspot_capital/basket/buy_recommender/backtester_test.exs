defmodule HottspotCapital.Basket.BuyRecommender.BackTesterTest do
  use HottspotCapital.Test.DataCase, concurrent: true

  alias HottspotCapital.Basket.BuyRecommender.BackTester
  alias HottspotCapital.Test.Factory
  alias HottspotCapital.Test.Stubs.StockQuoteStubs

  describe ".backtest" do
    test "returns percent correctness of reconmmendations over n tests" do
      ["HOTT", "NKE", "INTC", "PG", "MCD", "NFLX", "JPM"]
      |> Enum.zip(stubbed_closes_and_volumes())
      |> Enum.each(fn {symbol, stock_quotes} ->
        Factory.create_company(%{symbol: symbol})

        stock_quotes
        |> Enum.with_index()
        |> Enum.each(fn {[close, volume], index} ->
          Factory.create_stock_quote(%{
            close: close,
            date: Date.from_erl!({2019, 08, 26 - index}),
            symbol: symbol,
            volume: volume
          })
        end)
      end)

      accuracy = BackTester.backtest(10)

      assert accuracy >= 0 && accuracy <= 1
    end
  end

  defp stubbed_closes_and_volumes do
    ~w[
      7.8831e+02   4.0031e+05
      1.0738e+02   7.8350e+05
      1.4101e+02   9.2311e+05
      7.7134e+02   2.7024e+05
      4.4235e+02   1.4679e+05
      9.3625e+01   5.4075e+05
      2.3399e+02   2.9187e+05
      5.6567e+02   8.5775e+05
      8.1863e+02   8.7500e+05
      4.7856e+02   7.2641e+05

      8.3952e+02   9.3695e+05
      9.3939e+02   3.8813e+05
      1.9536e+02   6.1072e+05
      5.5885e+02   2.6160e+05
      9.2771e+02   1.7901e+05
      7.1686e+02   4.8918e+05
      4.6854e+02   5.8230e+03
      8.3198e+02   7.1293e+05
      2.5891e+02   4.6903e+05
      5.1803e+02   4.9108e+05

      7.0021e+01   5.6270e+05
      9.6286e+02   9.6104e+05
      4.7138e+02   1.4220e+05
      1.7981e+02   1.5557e+05
      3.5390e+01   2.3487e+05
      6.5747e+02   1.8430e+05
      6.1387e+02   5.1518e+05
      7.3903e+01   1.4756e+05
      1.4168e+01   6.8310e+04
      3.5732e+02   7.3744e+05

      2.0959e+02   6.2745e+05
      2.9633e+02   6.8213e+05
      2.3202e+02   6.7689e+03
      2.8761e+02   7.4810e+05
      5.0580e+02   9.6195e+05
      8.8646e+02   9.3182e+04
      6.2499e+02   7.8104e+05
      3.2781e+02   5.8971e+05
      8.4075e+02   9.5465e+05
      2.2888e+02   4.9970e+05

      5.7165e+02   4.7682e+05
      4.2220e+02   6.3500e+05
      4.5125e+02   8.7879e+05
      5.3027e+02   5.8535e+04
      9.3813e+02   1.4124e+05
      7.4329e+00   2.9327e+05
      8.7962e+02   5.4552e+05
      2.9496e+02   3.5409e+05
      8.5222e+02   2.5477e+04
      6.5124e+02   9.9649e+05

      4.1013e+02   2.2558e+05
      8.4032e+02   2.0043e+05
      6.9328e+02   3.0530e+05
      6.7145e+02   1.4767e+05
      2.7300e+02   6.0999e+05
      8.2502e+02   6.7451e+05
      8.4518e+02   6.7559e+05
      9.7262e+02   8.8426e+03
      3.2314e+02   8.8463e+05
      6.8154e+02   9.6453e+05

      6.3458e+02   6.7584e+05
      4.8819e+02   9.9273e+05
      3.8444e+02   6.4971e+05
      6.7476e+02   9.1020e+05
      9.4687e+02   8.5338e+05
      8.3402e+02   8.6297e+05
      6.5134e+02   2.8845e+05
      4.7537e+01   1.3146e+05
      7.2936e+01   8.3893e+05
      6.5417e+02   7.1187e+05
    ]
    |> StockQuoteStubs.group_closes_and_volumes(days: 10)
  end
end
