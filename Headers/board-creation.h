using namespace std;

//function that creates the board
vector < vector < string >> createBoard(int boardX, int boardY) {
  //defining variables
	int colLoop = 1;
  int maxAlphabet = 26;

	//alphabet array for X axis
  string alphabetArray[] = {"", "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

	//board notation
  string boxStr = "| ";
  string charSpace = " ";

	//updates board notation if the boardY is larger then 26
  if (boardY > 26) {
    boxStr = "|  ";
    charSpace = "  ";
  }

	//this vector is being set to the size of the board and filled with the box string
  vector < vector < string >> boardVect(boardX + 1, vector < string > (boardY + 1, boxStr));

	//for loop that goes through each index of the board
  for (int i = 0; i < boardVect.size(); i++) {
    for (int j = 0; j < boardVect[1].size(); j++) {
			//this for loop populates the X axis
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

			//this for loop populates the Y axis
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

	//returns the boardVect (an empty board with axis)
  return boardVect;
}