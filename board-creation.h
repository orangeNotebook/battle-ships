//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

vector < vector < string >> createBoard(int boardX, int boardY) {
  int colLoop = 1;
  int maxAlphabet = 26;
  string alphabetArray[] = {"", "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  string boxStr = "| ";
  string charSpace = " ";

  if (boardY > 26) {
    boxStr = "|  ";
    charSpace = "  ";
  }

  vector < vector < string >> boardVect(boardX + 1, vector < string > (boardY + 1, boxStr));

  for (int i = 0; i < boardVect.size(); i++) {
    for (int j = 0; j < boardVect[1].size(); j++) {

      if (i == 0) {
        if (j <= maxAlphabet) {
          boardVect[i][j] = charSpace + alphabetArray[j];
        } else if (j <= (maxAlphabet * (colLoop + 1))) {
          boardVect[i][j] = " " + alphabetArray[colLoop] + alphabetArray[j - (maxAlphabet * colLoop)];
          if (j == maxAlphabet * (colLoop + 1)) {
            colLoop++;
          }
        }
      }

      if (j == 0) {
        if (i >= 100) {
          boardVect[i][j] = (to_string(i) + "");
        } else if (i >= 10) {
          boardVect[i][j] = (to_string(i) + " ");
        } else {
          boardVect[i][j] = (" " + to_string(i) + " ");
        }

      }
      if (j == boardVect[1].size() && i == boardVect.size()) {
        boardVect[i][j] = ("| |");
      }

    }
  }

  return boardVect;
}