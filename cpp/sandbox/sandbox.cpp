#include <math.h>
#include <stdio.h> // printf

int main() {
  double a = -100;
  printf("%c$%'.2f\n", a > 0 ? '+' : '-', abs(a));
}
