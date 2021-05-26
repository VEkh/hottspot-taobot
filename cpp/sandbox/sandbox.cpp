// #include "lib/websockets/client/client.cpp" // WebSockets::Client
// #include <iostream>

// int main() {
//   WebSockets::Client client("wss://stream.data.alpaca.markets/v2/iex");
//   client.connect();
// }

#include <iostream>
#include <vector>

double avg(std::vector<double> vec) {
  double sum = 0;

  for (double ratio : vec) {
    sum += ratio;
  }

  return sum / vec.size();
}

int main() {
  double aapl = avg({
      (0.06 / 0.69),
      (0.10 / 0.72),
      (0.00 / 0.60),
      (0.30 / 0.50),
      (0.17 / 0.47),
      (0.14 / 0.43),
  });

  double amd = avg({
      (0.08 / 0.92),
      (0.47 / 0.98),
  });

  double ba = avg({(0.18 / 2.15), (0.50 / 2.15), (0.37 / 2.33), (0.40 / 1.62),
                   (0.40 / 1.10)});

  double coin =
      avg({(0.14 / 5.04), (3.17 / 5.74), (1.37 / 8.87), (1.81 / 8.96)});

  double fb = avg({
      (0.16 / 2.43),
      (0.02 / 2.43),
      (1.00 / 1.48),
      (1.24 / 1.87),
      (0.06 / 3.06),
      (0.94 / 1.91),
  });

  double msft = avg({(0.56 / 1.58)});

  double snap = avg({
      (0.05 / 1.04),
      (1.02 / 1.04),
      (0.25 / 0.82),
      (0.16 / 0.68),
  });

  double sq = avg({(2.07 / 4.00), (0.84 / 7.01)});

  double tsla = avg({
      (4.47 / 7.40),
      (9.13 / 13.81),
      (4.66 / 14.98),
  });

  std::cout << "AAPL: " << aapl << std::endl;
  std::cout << "AMD: " << amd << std::endl;
  std::cout << "BA: " << ba << std::endl;
  std::cout << "COIN: " << coin << std::endl;
  std::cout << "FB: " << fb << std::endl;
  std::cout << "MSFT: " << msft << std::endl;
  std::cout << "SNAP: " << snap << std::endl;
  std::cout << "SQ: " << sq << std::endl;
  std::cout << "TSLA: " << tsla << std::endl;

  std::cout << "Overal Average: "
            << avg({
                   aapl,
                   amd,
                   ba,
                   coin,
                   fb,
                   msft,
                   snap,
                   sq,
                   tsla,
               })
            << std::endl;
}
