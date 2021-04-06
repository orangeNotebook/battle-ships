#include "player-v-player.h"

using namespace std;

int playerVComputerGameLoop(vector < Player > players, char developerMode, int winScore) {
  char shootOption;
  bool gameRunning = true;
  int turn = 0;
  int turn2 = 1;
  string targetCoords;

  while (gameRunning) {
    if (turn == 0) {
      if (developerMode == 'Y') {
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        cout << "\n1. Fire manually\n2. Fire randomly\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

        players = shoot(players, turn, shootOption);
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      } else {
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        cout << "\n1. Fire manually\n2. Fire randomly\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

        players = shoot(players, turn, shootOption);
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      }

    } else {
      if (developerMode == 'Y') {
        Clear();
        cout << players[turn].name + "'s turn (only visible in developer mode)\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nComputers board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        players = shoot(players, turn, 2);
        Clear();
        cout << players[turn].name + "'s turn (only visible in developer mode)\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nComputers board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      } else {
        players = shoot(players, turn, 2);
      }
    }

		if (players[turn].score == winScore) {
      Clear();
      cout << players[turn].name + " wins!\n\n";
      pressAnyKey();
      Clear();
      gameRunning = false;
      return 0;
    }

    if (turn == 0) {
      turn = 1;
      turn2 = 0;
    } else {
      turn = 0;
      turn2 = 1;
    }
  }
  return 0;
}

//main function
int playerVComputer() {
  vector < Player > players = createPlayer(1);
  vector < int > Data = readFile();
  vector < Ship > ships = createShips(Data);
  vector < vector < string >> emptyBoard = createBoard(Data[0], Data[1]);

  char placeChoice;
  char developerMode;
	int winScore;

  cout << "Would you like to access developer mode (see computers ships and turn)\n\n[Y/N]: ";
  cin >> developerMode;
  developerMode = toupper(developerMode);

  for (int i = 0; i < players.size(); i++) {
    char choice;
    players[i].board = emptyBoard;
    players[i].targetBoard = emptyBoard;
    Clear();

    if (i == 0) {
      cout << players[i].name + "'s turn\n\n1. Place your boats manually\n2. Place your boats automatically\n\nPlease choose a way to set your board up: ";

      cin >> placeChoice;

      if (placeChoice == '1') {
				winScore = 0;
        for (int j = 0; j < ships.size(); j++) {
					winScore += ships[j].size;
          Clear();
          cout << players[i].name + "'s Board: \n";
          printBoard(players[i].board);
          cout << "\n";
          players[i] = ships[j].placeShip(players[i], placeChoice);
          cout << "\n";
        }
      } else {
				winScore = 0;
        for (int j = 0; j < ships.size(); j++) {
					winScore += ships[j].size;
          Clear();
          cout << players[i].name + "'s Board: \n";
          printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
          players[i] = ships[j].placeShip(players[i], placeChoice);
          cout << "\n";
        }
      }

      Clear();
      cout << players[i].name + "'s Board: \n";
      printBoard(players[i].board);
      cout << "\nAre you happy with your board layout? [Y, N]: ";
      cin >> choice;
      choice = toupper(choice);

      if (choice == 'N') {
        players[i].board = emptyBoard;
        i--;
      }

    } else {
      if (developerMode == 'Y') {
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
					printBoard(players[i].board);
					cout << "\nGenerating ship placement, please wait\n";
          players[i] = ships[j].placeShip(players[i], '2');
					Clear();
					cout << players[i].name + "'s Board: \n";
					printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
        }
        pressAnyKey();
      } else {
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
          // printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
          players[i] = ships[j].placeShip(players[i], '2');
          cout << "\n";
        }
      }
    }

  }

  playerVComputerGameLoop(players, developerMode, winScore);

  return 0;
}