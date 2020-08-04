/* Cora English
 * 127007634
 * HW 1: CoinMaker
 * CSCE 121-525
 */


#include <iostream>
using namespace std;
namespace cora {

int main() {

  // initializes dollars and cents to zero
  int dollars = 0;
  int cents = 0;

  cout << "Enter dollars: ";
  cin >> dollars;

  cout << "Enter cents: ";
  cin >> cents;

  // calculates total amount of money in coins instead of dollars and cents
  int centsRemaining = (dollars * 100) + cents;

  int numQuarters = centsRemaining / 25;
  centsRemaining %= 25;   // will be the amouont of change left after quarters are taken out

  int numDimes = centsRemaining / 10;
  centsRemaining %= 10;

  int numNickels = centsRemaining / 5;
  centsRemaining %= 5;

  int numPennies = centsRemaining;   // number will always be less than 5 at this point

  // sums the numbers for all individual coins to find the total amount of coins used
  int totalCoins = numQuarters + numDimes + numNickels + numPennies;

  cout << "Pennies: " << numPennies << endl;
  cout << "Nickels: " << numNickels << endl;
  cout << "Dimes: " << numDimes << endl;
  cout << "Quarters: " << numQuarters << endl << endl;
  cout << "Total coins used: " << totalCoins << endl;

} // end main

}
