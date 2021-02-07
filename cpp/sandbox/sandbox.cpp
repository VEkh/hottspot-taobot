#include <iostream>

// AAPL
// * Day Ranges (average: 0.01510235705884684):
//   * 2/5: 0.01135784492173261
//   * 2/4: 0.020616287600880426
//   * 2/3: 0.01591043017088978
//   * 2/2: 0.01252486554188454
// AMZN
// * Day Ranges (average: 0.024855701064759924):
//   * 2/5 0.022383247966254884
//   * 2/4 0.02072072072072072
//   * 2/3 0.0364963503649635
//   * 2/2 0.01982248520710059
// FB
// * Day Ranges (average: 0.017503487153850094):
//   * 2/5: 0.013118440779610194
//   * 2/4: 0.01557994082618638
//   * 2/3: 0.02017920337324002
//   * 2/2: 0.02113636363636379
// GOOG
// * Day Ranges (average: 0.02696434027923376):
//   * 2/5: 0.020859903381642654
//   * 2/4: 0.017399710004833254
//   * 2/3: 0.04775687409551375
//   * 2/2: 0.0218408736349454
// MSFT
// * Day Ranges (average: 0.015742886947924372):
//   * 2/5: 0.011806960326962036
//   * 2/4: 0.011827248001318737
//   * 2/3: 0.02433526735400932
//   * 2/2: 0.015002072109407395
// TSLA
// * Day Ranges (average: 0.032849434296456634):
//   * 2/5: 0.030532544378698172
//   * 2/4: 0.026994152046783675
//   * 2/3: 0.02852842580556897
//   * 2/2: 0.04534261495477572

// int main() { std::cout << (13.0 / 20) << std::endl; }

// const double STOP_LOSS_RATIO = 0.005;
// const double STOP_WIN_RATIO = 0.0025;
// Simulation Win Rates:
// * Note: Must exceed 2/3 to be profitable
// AAPL
// * Win Rate: 1/5
// AMZN
// * Win Rate: 2/6
// GOOG
// * Win Rate: 6/7 => 0.857143
// TSLA
// * Win Rate: 15/18 => 0.833333

const double ENTRY_DISPLACEMENT_RATIO = 0.0025;
const double STOP_LOSS_RATIO = 0.0025;
const double STOP_WIN_RATIO = 0.0025;
// Simulation Win Rates:
// * Note: Must exceed 2/3 to be profitable
// AAPL
// * Win Rate: 0/0
// AMZN
// * Win Rate: 0/0
// GOOG
// * Win Rate: 0/0
// TSLA
// * Win Rate: 13/20 => 0.65

int main() {
  const double price = 3320;
  const double entry_delta = price * ENTRY_DISPLACEMENT_RATIO;

  const double buy_entry_price = price + entry_delta;
  const double sell_short_entry_price = price - entry_delta;

  const double buy_loss_price = buy_entry_price - (price * STOP_LOSS_RATIO);
  const double buy_win_price = buy_entry_price + (price * STOP_WIN_RATIO);

  const double sell_short_loss_price =
      sell_short_entry_price + (price * STOP_LOSS_RATIO);
  const double sell_short_win_price =
      sell_short_entry_price - (price * STOP_WIN_RATIO);

  std::cout << "BUY        => Entry: $" << buy_entry_price << " • Win: $"
            << buy_win_price << " • Loss: $" << buy_loss_price << std::endl;

  std::cout << "SELL_SHORT => Entry: $" << sell_short_entry_price
            << " • Win:
      $ "
            << sell_short_win_price << " • Loss: $" << sell_short_loss_price
            << std::endl;
}
