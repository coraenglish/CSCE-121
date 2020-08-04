#include <iostream>
#include <fstream>
using namespace std;


/*  Function readPrefs
 *  fileName: c-style String, i.e., array of chars ended by ‘\0’
 *  ngames:   number of games
 *  prefs:    array of integers created with MAX_NB_GAMES=200
 *            positions
 *  Return value: reads your game preferences from file fileName and stores the
 *  information in the array prefs, returning the number of valid lines present
 *  in the file. For any game without a rating provided in the file, you should
 *  store 0 as the rating in its entry in array prefs. If there is a problem with
 *  opening the file fileName, the function returns -1
 */
int readPrefs(char fileName[], int ngames, int prefs[]) {

  int validLines = 0;
  int i = 0; int j = 0;

  ifstream ifs{fileName};

  while (!ifs.eof()) {
    ifs >> i >> j;
    if (ifs.bad()) {
        return -1;
        break;
    } else {
        if ((i >= 0 && i < 200) && (j >= 0 && j <= 5)) {
          prefs[i] = j;
          validLines += 1;
        }
      }
    }
  return validLines;
}



/*  Function readPlan
 *  fileName: c-style String, i.e., array of chars ended by ‘\0’
 *  plan:    array of integers created with 365 positions
 *  Return value:  reads your cousins’ plans from file fileName and stores the
 * information in the array plan. You may assume that the information in the file
 * is in chronological order, every line contains valid information, and no day is
 * missing. Each line of the file contains the day (an integer between 1 and 365)
 * and the id for the game planned for the day. If there is a problem with opening
 * the file fileName, the function returns -1; otherwise, it returns 0.
 */
int readPlan(char fileName[], int ngames, int plan[]) {

  int i = 0; int j = 0;

  ifstream ifs{fileName};

  while (!ifs.eof()) {
    ifs >> i >> j;
    if (ifs.bad()) {
        return -1;
    } else {
        if (i > 0 && i <= 365) {
          plan[i] = j;
          //cout << i << '\t' << plan[i] << endl;
        }
      }
    }
  return 0;
}



/*  Function computeFunLevel
 *  start:  first day of the vacation (1 <= start < 365)
 *  duration: number of vacation days (duration >= 1)
 *  gamePrefs: gamePrefs[k] indicates the rating specified for game k
 *  ngames: number of elements in the array gamePrefs
 *  plan: array with 366 positions with the sequence of games
 *        to be played over the year. In other words,
 *        plan[k] indicates the game planned for day k (1 <= k <= 365)
 *  Return value: returns the sum of the ratings for games played during the
 * vacation period. If the duration is longer than the number of days left in
 * the year, the function returns -1.
 */
int computeFunLevel (int start, int duration, int gamePrefs[], int ngames, int plan[]) {

  int funLevel = 0;

  if ((start+duration-1) > 365) {
    return -1;
  } else {
    for (int i = start; i < (start + duration); i++) {
    funLevel += gamePrefs[plan[i]];
    }
    return funLevel;
  }
}


/*  Function findBestVacation
*  duration: number of vacation days
*  gamePrefs: gamePrefs[k] indicates the rate specified for game k
*  ngames: number of elements in the array gamePrefs
*  plan: array with 366 positions with the sequence of games
*        to be played over the year. In other words,
*        plan[k] indicates the game planned for day k (1 <= k <= 365)
*  Return value: Explained below.
*/
int findBestVacation (int duration,  int gamePrefs[], int ngames, int plan[]) {

  int bestStartDate = 1;
  int highestFunLevel = 0;
  int funLeveli = 0;

  for (int i = 1; i < 366; i++) {
    funLeveli = computeFunLevel(i, duration, gamePrefs, ngames, plan);
    if (funLeveli > highestFunLevel) {
      highestFunLevel = funLeveli;
      bestStartDate = i;
    }
  }
  return bestStartDate;
}
