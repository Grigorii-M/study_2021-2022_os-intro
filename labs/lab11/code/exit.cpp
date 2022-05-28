#include <iostream>

int main() {
  int n;
  std::cin >> n;

  if (n > 0) {
    exit(2);
  } else if (n == 0) {
    exit(1);
  } else {
    exit(0);
  }

  return 0;
}
