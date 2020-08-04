#include <iostream>
#include "functions.h"
using namespace std;

int main() {
  int a = 0;
  int b = 0;
  cout << "Enter numbers a <= b: ";
  cin >> a >> b;
  int validNums = b - a + 1;

  if ((a > 0) && (a <= b) && (b <= 10000)) {
    for (int i = a; i <= b; ++i) {
      for (int j = 0; j < 10; ++j) {
        if (countDigitOccurrences(i, j) > 1) {
          validNums -= 1;
          break;
        }
      }
    }
    cout << "There are " << validNums << " valid numbers between " << a
    << " and " << b << endl;
  } else {
    cout << "Invalid input" << endl;
  }
}
