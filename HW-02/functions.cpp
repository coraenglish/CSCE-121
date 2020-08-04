#include <iostream>
using namespace std;

int countDigitOccurrences (int n, int digit) {
  int repeatingNums = 0;
  while (n > 0) {
    int lastDigit = n % 10;
    n /= 10;
    if (lastDigit == digit) {
      repeatingNums += 1;
    }
  }
  return repeatingNums;
}
