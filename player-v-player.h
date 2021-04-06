//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
#include <cctype>
#include <cstdio>

#include "read-config.h"
#include "shoot.h"


using namespace std;

void Clear() {
  cout << "\x1B[2J\x1B[H";
}

void pressAnyKey() {
  //codes here
  cout << "Press any key to continue...";
  cin.ignore();
  cin.get();
}

void printBoard(vector < vector < string >> Board) {
  for (int i = 0; i < Board.size(); i++) {
    for (int j = 0; j < Board[1].size(); j++) {
      cout << Board[i][j] << "";
    }
    cout << endl;
  }
}

vector < Ship > createShips(vector < int > Data) {
  Ship ship;
  vector < Ship > ships;
  for (int i = 0; i < (Data.size() - 2); i++) {
    ship.size = Data[i + 2];
    ship.name = ("Ship " + to_string(i + 1));
    ships.push_back(ship);
  }
  return ships;
}

// vector < Player > shoot(vector < Player > players, int turn) {
//   string coords;
//   string checkShip = "|S";
//   string checkEmpty = "| ";
//   string hitMarker = "|H";
//   string missMarker = "|M";
//   string charSpace = " ";
//   int targetPlayer;
//   char targetX;
//   int intTargetX;
//   int targetY;
//   string str1;
//   string str2;
//   char shootOption;

//   cout << "\n1. Fire manually\n2. Fire randomly\n\nPlease choose how you would like to fire: ";
//   cin >> shootOption;

//   if (shootOption == '1') {
//     cout << "\nChoose where to shoot [eg. F2]: ";
//     cin >> coords;
//     coords = makeUpper(coords);
//   } else {
//     coords = generateCoord(players[0].board.size());
//   }

//   if (turn == 0) {
//     targetPlayer = 1;
//   } else {
//     targetPlayer = 0;
//   }

//   if (coords.size() == 2) {
//     targetX = coords[0];
//     targetY = (coords[1] - '0');

//   } else if (coords.size() == 0 || coords.size() >= 4) {
//     cout << "Invalid coordinates, please try again\n";
//     return shoot(players, turn);

//   } else if (coords.size() == 3) {
//     str1 += coords[1];
//     str1 += coords[2];

//     str2 += coords[0];
//     str2 += coords[1];
//     if (stoi(str1) >= 1 && stoi(str1) <= players[targetPlayer].board.size()) {
//       targetY = (stoi(str1));
//       targetX = coords[0];

//     } else {
//       targetY = (coords[2] - '0');
//       targetX = (str2[1]);
//     }
//   }

//   string coordsX(1, targetX);

//   for (int i = 0; i < players[targetPlayer].board.size(); i++) {
//     if (players[targetPlayer].board[i].size() > 26) {
//       checkShip = "| S";
//       checkEmpty = "|  ";
//       hitMarker = "| H";
//       missMarker = "| M";
//       charSpace = "  ";
//     }
//     for (int j = 0; j < players[targetPlayer].board[i].size(); j++) {

//       if ((charSpace + coordsX) == players[targetPlayer].board[i][j]) {
//         intTargetX = j;
//       }

//     }
//   }
//   if (players[targetPlayer].board[targetY][intTargetX] == checkShip) {
//     players[targetPlayer].board[targetY][intTargetX] = hitMarker;
//     players[turn].targetBoard[targetY][intTargetX] = hitMarker;
//     players[turn].score++;
//   } else if (players[targetPlayer].board[targetY][intTargetX] == checkEmpty) {
//     players[targetPlayer].board[targetY][intTargetX] = missMarker;
//     players[turn].targetBoard[targetY][intTargetX] = missMarker;
//   } else if (players[targetPlayer].board[targetY][intTargetX] == hitMarker || players[targetPlayer].board[targetY][intTargetX] == missMarker) {
//     if (shootOption == '1') {
//       cout << "\nCoordinate already checked, please enter a different coordinate: \n";
//     }
//     return shoot(players, turn);
//   }

//   return players;
// }

int playerVPlayerGameLoop(vector < Player > players, int winScore) {
  bool gameRunning = true;
  int turn = 0;
  string targetCoords;
	char shootOption;

  while (gameRunning) {
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
		cout << "\nShip fragments left: " + to_string(winScore - players[turn].score) + "\n";

    if (players[turn].score == winScore) {
      Clear();
      cout << players[turn].name + " wins!\n\n";
      pressAnyKey();
      Clear();
      gameRunning = false;
      return 0;
    }

    pressAnyKey();
    Clear();
    cout << "Please hand the game to the next player\n\n";
    pressAnyKey();
    Clear();

    if (turn == 0) {
      turn = 1;
    } else {
      turn = 0;
    }
  }
  return 0;
}


//main function
int playerVPlayer() {
  vector < Player > players = createPlayer(2);
  vector < int > Data = readFile();
  vector < Ship > ships = createShips(Data);
  vector < vector < string >> emptyBoard = createBoard(Data[0], Data[1]);

	string coords = "";
  char placeChoice;
	int winScore = 0;

  for (int i = 0; i < players.size(); i++) {
    char choice;
    players[i].board = emptyBoard;
    players[i].targetBoard = emptyBoard;
    Clear();

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

  }

  playerVPlayerGameLoop(players, winScore);

  return 0;
}