//Utility file for functions
void printBoard(vector < vector < string >> Board) {
  for (int i = 0; i < Board.size(); i++) {
    for (int j = 0; j < Board[1].size(); j++) {
      cout << Board[i][j] << "";
    }
    cout << endl;
  }
}

void Clear() {
  cout << "\x1B[2J\x1B[H";
}

void pressAnyKey() {
  cout << "Press any key to continue...";
  cin.ignore();
  cin.get();
}

string makeUpper(string str) {
  for (int i = 0; i < str.size(); i++) {
    str[i] = toupper(str[i]);
  }
  return str;
}

void wait(int length){
			int microsecond = 1000000;
			usleep(length * microsecond);
		}

string generateCoord(int size) {
  string coords = "";
  string alphabetArray[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  int number, letter;
  bool invalidCoord = true;
  size -= 1;

	wait(1);

  while (invalidCoord) {
    srand(time(0));;
    number = ((rand() % size) + 1);

    if (number <= size && number >= 1) {
      invalidCoord = false;
    }
  }

  if (size <= 26) {
    random_shuffle(( & alphabetArray[0]), ( & alphabetArray[size - 1]));

    srand(time(0));
    letter = (rand() % (size));
    coords += alphabetArray[letter] + to_string(number);
  } else {
    random_shuffle(begin(alphabetArray), end(alphabetArray));

    srand(time(0));
    letter = (rand() % 26);
    coords += "A" + alphabetArray[letter] + to_string(number);
  }
  return coords;
}