//importing
#include "ship-class.h"
#include "board-creation.h"

//Shoot function
vector < Player > shoot(vector < Player > players, int turn, char shootOption) {
	//coords store where user wants to shoot
  string coords;

	//next couple are default notations to check / set grid
  string checkShip = "|S";
  string checkEmpty = "| ";
  string hitMarker = "|H";
  string missMarker = "|M";
  string charSpace = " ";

	//the index of the player being targetted
  int targetPlayer;
	//the X target from coords (eg. A3 -> A)
  char targetX;
	//the X target once it's converted from coords to its int coord equivalent
  int intTargetX;
	//the Y target from the coords (eg. A3 -> 3)
  int targetY;

	//temporary strings to hold conversion from larger coordinates (eg. A32)
  string str1;
  string str2;
	bool twoString = false;

	//checking if the user wants to manually shoot
  if (shootOption == '1') {
		//asks where the user wants to shoot
    cout << "\nChoose where to shoot [eg. F2]: ";
    cin >> coords;
    coords = makeUpper(coords);
  } else {
    coords = generateCoord(players[0].board.size()); //if not manually shooting, runs generateCoord to generate a random coordinate
  }

	//determining the target players id
  if (turn == 0) {
    targetPlayer = 1;
  } else {
    targetPlayer = 0;
  }

	//next few lines are to split up the coordinates from eg. "A3" to 'A' and 3, or "A23" to 'A' and 23

	//if the size of coords is 2 split it in the middle
  if (coords.size() == 2) {
    targetX = coords[0];
    targetY = (coords[1] - '0');

	//if the coords size is 0 or larger then 4 (max coord size AA10) then re-run shoot to get a valid coord
  } else if (coords.size() == 0 || coords.size() >= 4) {
    cout << "Invalid coordinates, please try again\n";
    return shoot(players, turn, shootOption);

	//if coord is 3 then split it accordingly
  } else if (coords.size() == 3) {
		//sets temporary strings to determine if the coord is (letter-letter-number) or (letter-number-number)
    str1 += coords[1];
    str1 += coords[2];

    str2 += coords[0];
    str2 += coords[1];

		//checks if the order is (letter-number-number) by determining if str1 is a number
    if (stoi(str1) >= 1 && stoi(str1) <= players[targetPlayer].board.size()) {
			//set targetY to the Y coord
      targetY = (stoi(str1));
      //set targetX to first char
			targetX = coords[0];
    } else {
			//if not (letter-number-number) sets targetY to last char converted to number (eg. AB3 -> 3)
      targetY = (coords[2] - '0');
			//sets targetX to the second part of the coord (eg. AB3 -> B)
      targetX = (str2[1]);
			twoString = true;
    }
  }

	//sets a string coordsX into a string version of targetX for comparison
  string coordsX(1, targetX);

	//loop that converts the X from a char to an int
  for (int i = 0; i < players[targetPlayer].board.size(); i++) {
		//checks the size of the board and changes notation accordingly for future comparison
    if (players[targetPlayer].board[i].size() > 26) {
      checkShip = "| S";
      checkEmpty = "|  ";
      hitMarker = "| H";
      missMarker = "| M";
      charSpace = "  ";
    }

		//for loop that loops through the X axis and checks if it matches the provided coord for X
    for (int j = 0; j < players[targetPlayer].board[i].size(); j++) {
			//checks if the input had 2 letters (for bigger board compatibility)
			if (twoString){
				if (("|" + str2) == players[targetPlayer].board[i][j]) {
        //if X coord found in grid, gets that index and sets it to the intTargetX for grid referencing
				intTargetX = j;
      }
			}
      else if ((charSpace + coordsX) == players[targetPlayer].board[i][j]) {
        //if X coord found in grid, gets that index and sets it to the intTargetX for grid referencing
				intTargetX = j;
      }
    }
  }
	
	//Next lines check the grid with the converted string to x and y int coordinates and determines if the shot hit, missed or has already been checked

	//checks if hit and converts the coordinate notation if yes
  if (players[targetPlayer].board[targetY][intTargetX] == checkShip) {
    players[targetPlayer].board[targetY][intTargetX] = hitMarker;
    players[turn].targetBoard[targetY][intTargetX] = hitMarker;
		players[turn].score++;
  } 
	//checks if missed and converts the coordinates notation if yes
	else if (players[targetPlayer].board[targetY][intTargetX] == checkEmpty) {
    players[targetPlayer].board[targetY][intTargetX] = missMarker;
    players[turn].targetBoard[targetY][intTargetX] = missMarker;
  } 
	//Checks if the coordinate has already been checked, if yes and the user is manually shooting returns an error message and re-runs shoot, otherwise just re-runs
	else if (players[targetPlayer].board[targetY][intTargetX] == hitMarker || players[targetPlayer].board[targetY][intTargetX] == missMarker) {
    if (shootOption == '1') {
      cout << "\nCoordinate already checked, please enter a different coordinate: \n";
    }
    return shoot(players, turn, shootOption);
  }

	//returns the updated players class (updated boards and player score)
  return players;
}