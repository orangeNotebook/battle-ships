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
#include "player-class.h"

string makeUpper(string str) {
  for (int i = 0; i < str.size(); i++) {
    str[i] = toupper(str[i]);
  }
  return str;
}

string generateCoord(int size) {
  string coords = "";
  string alphabetArray[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  int number, letter;
  bool invalidCoord = true;
  size -= 1;

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

class Ship {
  public:
    string name;
    int size;

  int checkLength(string coords) {
    if (coords.size() == 1) {
      return 0;
    } else if (coords.size() == 2) {
      return 2;
    } else if (coords.size() == 3) {
      return 3;
    } else if (coords.size() == 4) {
      return 4;
    }
    return 0;
  }

  char generateDirection(vector < int > coordsVect, int maxSize) {
    char directionArray[] = {
      'L',
      'R',
      'U',
      'D'
    };
    int number, letter;
    time_t nTime;
    bool invalidDirection = true;
    int microsecond = 1000000;

    int coordX = coordsVect[1];
    int coordY = coordsVect[0];

    while (invalidDirection) {
      srand((unsigned) time( & nTime));
      number = (rand() % 4);
      switch (directionArray[number]) {
      case 'L':
        if (coordX - this -> size >= 0) {
          invalidDirection = false;
        }
        break;
      case 'R':
        if (coordX + this -> size <= maxSize) {
          invalidDirection = false;
        }
        break;
      case 'D':
        if (coordY + this -> size <= maxSize) {
          invalidDirection = false;
        }
        break;
      case 'U':
        if (coordY - this -> size >= 0) {
          invalidDirection = false;
        }
        break;
      }
      usleep(1 * microsecond);
    }

    return directionArray[number];
  }

  //
  Player placeShip(Player player) {
    vector < int > coordsVect;
    int k = 0;
    string coords;
    char direction;
    bool notPlaced = true;
    int shipY;
    char shipX;
    string str1 = "";
    string str2 = "";
    string charSpace = " ";
    string boxStr = "|S";
    bool invalidDirection = true;

    coords = generateCoord(player.board.size());

    int length = checkLength(coords);

    if (length == 2) {
      shipX = coords[0];
      shipY = (coords[1] - '0');

    } else if (length == 0) {
      cout << "Invalid coordinates, please try again\n";
      return this -> placeShip(player);

    } else if (length == 3) {
      str1 += coords[1];
      str1 += coords[2];

      str2 += coords[0];
      str2 += coords[1];
      if (stoi(str1) >= 1 && stoi(str1) <= player.board.size()) {
        shipY = (stoi(str1));
        shipX = coords[0];

      } else {
        shipY = (coords[2] - '0');
        shipX = (str2[1]);
      }
    }

    string coordsX(1, shipX);

    for (int i = 0; i < player.board.size(); i++) {
      for (int j = 0; j < player.board[i].size(); j++) {
        //cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";

        if (player.board[i].size() > 26) {
          boxStr = "| S";
          charSpace = "  ";

          if ((charSpace + str2[0] + str2[1]) == player.board[i][j]) {
            coordsVect.push_back(shipY);
            coordsVect.push_back(j);

          } else if ((charSpace + coordsX) == player.board[i][j]) {
            coordsVect.push_back(shipY);
            coordsVect.push_back(j);

          }
        } else if ((charSpace + coordsX) == player.board[i][j]) {
          coordsVect.push_back(shipY);
          coordsVect.push_back(j);

        }
      }
    }

    direction = this -> generateDirection(coordsVect, player.board.size());

    while (notPlaced) {
      switch (direction) {
      case 'L':
        player.board[coordsVect[0]][coordsVect[1] - k] = boxStr;
        if ((coordsVect[1] - (k + 1)) == (coordsVect[1] - this -> size)) {
          notPlaced = false;
        }
        break;
      case 'R':
        player.board[coordsVect[0]][coordsVect[1] + k] = boxStr;
        if ((coordsVect[1] + (k + 1)) == (coordsVect[1] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'D':
        player.board[coordsVect[0] + k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] + (k + 1)) == (coordsVect[0] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'U':
        player.board[coordsVect[0] - k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] - (k + 1)) == (coordsVect[0] - this -> size)) {
          notPlaced = false;
        }
        break;
      }
      k++;
    }

    // cout << "Boat placed: '" + coords + "' facing '" +direction + "'";
    // pressAnyKey();
    return player;
  }

  //old one
  Player place(Player player) {
    vector < int > coordsVect;
    int k = 0;
    char placeOption;
    string coords;
    char direction;
    bool notPlaced = true;
    int shipY;
    char shipX;
    string str1 = "";
    string str2 = "";
    string charSpace = " ";
    string boxStr = "|S";

    cout << "\nBoat size: " + to_string(this -> size) + "\nWhere would you like to place this boat [eg. F2]: ";
    cin >> (coords);
    coords = makeUpper(coords);

    int length = checkLength(coords);

    if (length == 2) {
      shipX = coords[0];
      shipY = (coords[1] - '0');

    } else if (length == 0) {
      cout << "Invalid coordinates, please try again\n";
      return this -> place(player);

    } else if (length == 3) {
      str1 += coords[1];
      str1 += coords[2];

      str2 += coords[0];
      str2 += coords[1];
      if (stoi(str1) >= 1 && stoi(str1) <= player.board.size()) {
        shipY = (stoi(str1));
        shipX = coords[0];

      } else {
        shipY = (coords[2] - '0');
        shipX = (str2[1]);
      }
    }

    string coordsX(1, shipX);

    for (int i = 0; i < player.board.size(); i++) {
      for (int j = 0; j < player.board[i].size(); j++) {
        //cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";
        if (player.board[i].size() > 26) {
          boxStr = "| S";
          charSpace = "  ";

          if ((charSpace + str2[0] + str2[1]) == player.board[i][j]) {
            coordsVect.push_back(shipY);
            coordsVect.push_back(j);
            cout << to_string(coordsVect[0]);
            cout << to_string(coordsVect[1]);
          } else if ((charSpace + coordsX) == player.board[i][j]) {
            coordsVect.push_back(shipY);
            coordsVect.push_back(j);
            cout << to_string(coordsVect[0]);
            cout << to_string(coordsVect[1]);
          }
        } else if ((charSpace + coordsX) == player.board[i][j]) {
          coordsVect.push_back(shipY);
          coordsVect.push_back(j);
          cout << to_string(coordsVect[0]);
          cout << to_string(coordsVect[1]);
        }
      }
    }

    cout << "What direction should it face? [L, R, U, D]: ";
    cin >> direction;
    direction = toupper(direction);

    while (notPlaced) {

      switch (direction) {
      case 'L':
        player.board[coordsVect[0]][coordsVect[1] - k] = boxStr;
        if ((coordsVect[1] - (k + 1)) == (coordsVect[1] - this -> size)) {
          notPlaced = false;
        }
        break;
      case 'R':
        player.board[coordsVect[0]][coordsVect[1] + k] = boxStr;
        if ((coordsVect[1] + (k + 1)) == (coordsVect[1] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'D':
        player.board[coordsVect[0] + k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] + (k + 1)) == (coordsVect[0] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'U':
        player.board[coordsVect[0] - k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] - (k + 1)) == (coordsVect[0] - this -> size)) {
          notPlaced = false;
        }
        break;
      }
      k++;
    }

    return player;
  }
};