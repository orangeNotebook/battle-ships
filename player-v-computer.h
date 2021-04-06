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

#include "player-v-player.h"


using namespace std;

vector < Player > shoot2(vector < Player > players, int turn, char shootOption) {
  string coords;
  string checkShip = "|S";
  string checkEmpty = "| ";
  string hitMarker = "|H";
  string missMarker = "|M";
  string charSpace = " ";
  int targetPlayer;
  char targetX;
  int intTargetX;
  int targetY;
  string str1;
  string str2;

  if (shootOption == '1') {
    cout << "\nChoose where to shoot [eg. F2]: ";
    cin >> coords;
    coords = makeUpper(coords);
  } else {
    coords = generateCoord(players[0].board.size());
  }

  if (turn == 0) {
    targetPlayer = 1;
  } else {
    targetPlayer = 0;
  }

  if (coords.size() == 2) {
    targetX = coords[0];
    targetY = (coords[1] - '0');

  } else if (coords.size() == 0 || coords.size() >= 4) {
    cout << "Invalid coordinates, please try again\n";
    return shoot2(players, turn, shootOption);

  } else if (coords.size() == 3) {
    str1 += coords[1];
    str1 += coords[2];

    str2 += coords[0];
    str2 += coords[1];
    if (stoi(str1) >= 1 && stoi(str1) <= players[targetPlayer].board.size()) {
      targetY = (stoi(str1));
      targetX = coords[0];

    } else {
      targetY = (coords[2] - '0');
      targetX = (str2[1]);
    }
  }

  string coordsX(1, targetX);

  for (int i = 0; i < players[targetPlayer].board.size(); i++) {
    if (players[targetPlayer].board[i].size() > 26) {
      checkShip = "| S";
      checkEmpty = "|  ";
      hitMarker = "| H";
      missMarker = "| M";
      charSpace = "  ";
    }
    for (int j = 0; j < players[targetPlayer].board[i].size(); j++) {

      if ((charSpace + coordsX) == players[targetPlayer].board[i][j]) {
        intTargetX = j;
      }
    }
  }
  if (players[targetPlayer].board[targetY][intTargetX] == checkShip) {
    players[targetPlayer].board[targetY][intTargetX] = hitMarker;
    players[turn].targetBoard[targetY][intTargetX] = hitMarker;
  } else if (players[targetPlayer].board[targetY][intTargetX] == checkEmpty) {
    players[targetPlayer].board[targetY][intTargetX] = missMarker;
    players[turn].targetBoard[targetY][intTargetX] = missMarker;
  } else if (players[targetPlayer].board[targetY][intTargetX] == hitMarker || players[targetPlayer].board[targetY][intTargetX] == missMarker) {
    if (shootOption == '1') {
      cout << "\nCoordinate already checked, please enter a different coordinate: \n";
    }
    return shoot2(players, turn, shootOption);
  }

  return players;
}

int gameLoop2(vector < Player > players, char developerMode) {
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

        cout << "\n1. Fire manually\n2. Fire randomly\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

        players = shoot2(players, turn, shootOption);
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
        pressAnyKey();
        Clear();
      } else {
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);

        cout << "\n1. Fire manually\n2. Fire randomly\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

        players = shoot2(players, turn, shootOption);
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
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
        pressAnyKey();
        players = shoot2(players, turn, 2);
        Clear();
        cout << players[turn].name + "'s turn (only visible in developer mode)\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nComputers board: \n";
        printBoard(players[turn].board);
        pressAnyKey();
        Clear();
      } else {
        players = shoot2(players, turn, 2);
      }
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
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
          printBoard(players[i].board);
          cout << "\n";
          players[i] = ships[j].place(players[i]);
          cout << "\n";
        }
      } else {
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
          printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
          players[i] = ships[j].placeShip(players[i]);
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
          cout << "\n";
          players[i] = ships[j].placeShip(players[i]);
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
          players[i] = ships[j].placeShip(players[i]);
          cout << "\n";
        }
      }
    }

  }

  gameLoop2(players, developerMode);

  return 0;
}