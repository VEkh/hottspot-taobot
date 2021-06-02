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
      (0.00 / 0.54),
      (0.25 / 0.65),
      (0.24 / 0.88),
      (0.10 / 0.48),
      (0.12 / 0.57),
      (0.23 / 0.52),
      (0.44 / 0.66),
      (0.17 / 0.17),
      (0.23 / 0.50),
      (0.12 / 0.60),
  });

  double amd = avg({
      (0.12 / 0.72),
      (0.27 / 0.46),
      (0.09 / 0.64),
      (0.04 / 0.36),
  });

  double ba = avg({});

  double fb = avg({});

  double msft = avg({});

  double snap = avg({});

  double tsla = avg({});

  std::cout << "AAPL: " << aapl << std::endl;
  std::cout << "AMD: " << amd << std::endl;
  std::cout << "BA: " << ba << std::endl;
  std::cout << "FB: " << fb << std::endl;
  std::cout << "MSFT: " << msft << std::endl;
  std::cout << "SNAP: " << snap << std::endl;
  std::cout << "TSLA: " << tsla << std::endl;

  std::cout << "Overall Average: "
            << avg({
                   aapl,
                   amd,
                   ba,
                   fb,
                   msft,
                   snap,
                   tsla,
               })
            << std::endl;
}
