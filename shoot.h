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


#include "ship-class.h"
#include "board-creation.h"


vector < Player > shoot(vector < Player > players, int turn, char shootOption) {
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
    return shoot(players, turn, shootOption);

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
		players[turn].score++;
  } else if (players[targetPlayer].board[targetY][intTargetX] == checkEmpty) {
    players[targetPlayer].board[targetY][intTargetX] = missMarker;
    players[turn].targetBoard[targetY][intTargetX] = missMarker;
  } else if (players[targetPlayer].board[targetY][intTargetX] == hitMarker || players[targetPlayer].board[targetY][intTargetX] == missMarker) {
    if (shootOption == '1') {
      cout << "\nCoordinate already checked, please enter a different coordinate: \n";
    }
    return shoot(players, turn, shootOption);
  }

  return players;
}