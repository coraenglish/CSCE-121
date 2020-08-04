#include <iostream>
#include <fstream>
#include "functions.h"
#include "provided.h"
using namespace std;

int main() {

  int ngames = 0;
  int duration = 0;
  int MAX_TITLE_SIZE = 128;
  char gameTitles[255];
  char preferencesFile[255];
  char planFile[255];
  int MAX_NB_GAMES = 200;
  int prefsList[MAX_NB_GAMES];
  int planList[366];
  int readPrefsReturn = 0;
  int readPlanReturn = 0;
  int readGameTitlesReturn = 0;
  int bestStartDate = 1;
  char gameTitlesList[MAX_NB_GAMES][128];


  cout << "Please enter ngames and duration: ";
  cin >> ngames >> duration;

  if (((ngames > 200) || (ngames < 0)) || ((duration > 365) || (duration < 0))) {
    cout << "Invalid input.";
    return -1;
  } else {

    cout << "Please enter name of file with titles: ";
    cin >> gameTitles;
    cout << "Please enter name of file with preferences: ";
    cin >> preferencesFile;
    cout << "Please enter name of file with plan: ";
    cin >> planFile;

    ifstream ifs{gameTitles};
    if (!ifs.is_open()) {
      cout << "Invalid file." << endl;
      return 1;
    } else {
      ifstream ifs{preferencesFile};
      if (!ifs.is_open()) {
        cout << "Invalid file." << endl;
        return 1;
      }  else {
        ifstream ifs{planFile};
        if (!ifs.is_open()) {
          cout << "Invalid file." << endl;
          return 1;
        }
      }
    }

    for (int k = 0; k < 200; k++) {
      prefsList[k] = 0;
    }

    for (int k = 0; k < 366; k++) {
      planList[k] = 0;
    }

    readPrefsReturn = readPrefs(preferencesFile, ngames, prefsList);
    readPlanReturn = readPlan(planFile, ngames, planList);

    int gamePrefsList[ngames];
    for (int i = 0; i < ngames; ++i) {
      gamePrefsList[i] = prefsList[i];
    }

    if (computeFunLevel(1, duration, gamePrefsList, ngames, planList) != -1) {
      bestStartDate = findBestVacation (duration, gamePrefsList, ngames, planList);
    }

    readGameTitlesReturn = readGameTitles (gameTitles, ngames, gameTitlesList);
    if (readGameTitlesReturn != -1) {
      cout << "Best start day is " << bestStartDate << endl;
      cout << "Games to be played:" << endl;
      printGamesPlayedInVacation(bestStartDate, duration, planList, gameTitlesList, ngames);
    }

  }


}
