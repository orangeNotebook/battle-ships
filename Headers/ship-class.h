//importing
#include "player-class.h"
#include "utility.h"

//Creating the ship class
class Ship {
	//Name and Size properties are stored publicly for ease of access
  public:
    string name;
    int size;

	//check length method used for ship placement
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

		
	//Method to validate if a direction is within the board boundries
	bool validateDirection(vector < int > coordsVect, int maxSize, char direction) {
		int coordX = coordsVect[1];
		int coordY = coordsVect[0];

		//switch case determining if provided direction is within board boundries for its given coordinates
		switch (direction) {
			case 'L':
				if (coordX - this -> size >= 0) {
					return true;
				}
				break;
			case 'R':
				if (coordX + this -> size <= maxSize) {
					return true;
				}
				break;
			case 'D':
				if (coordY + this -> size <= maxSize) {
					return true;
				}
				break;
			case 'U':
				if (coordY - this -> size >= 0) {
					return true;
				}
				break;
			}
		return false;
	}

	//method to generate a random direction
  char generateDirection(vector < int > coordsVect, int maxSize) {
		//a char array containing all available directions
    char directionArray[] = {'L','R','U','D'};

		//variables to store and generate random number
    int number;
    time_t nTime;

		//bool to make sure direction generated wont make the ship go off the board
    bool invalidDirection = true;
    
		//while loop that generates random directions until one is valid
    while (invalidDirection) {
			//generates a random number between 0 and 3
      srand((unsigned) time( & nTime));
      number = (rand() % 4);

			//checks if the index of directionArray set to number is valid (eg. if number = 2, directionArray[number] -> 'U', then this gets checked in validateDirection)
       if (validateDirection(coordsVect, maxSize, directionArray[number])) {
          invalidDirection = false; //if valid stop loop
        }
			//if not valid, wait 1 second before regenerating direction (direction is generated from system time, this stops the program from creating multiple of the same direction after eachother and crashing the program)
      wait(1);
    }

		//returns the valid generated direction
    return directionArray[number];
  }



  //Place ship method used for placing the ship on a players grid
  Player placeShip(Player player, char placeType) {
		//vector for ship place coordinates
    vector < int > coordsVect;
		//string to hold user input or generated coords
    string coords;
		//character to hold direction
    char direction;
		//K and Y used for direction validation
		int k = 0;
    int y = 0;
    int shipY;
    char shipX;
		//Temporary strings used to convert larger coordinates
    string str1 = "";
    string str2 = "";
		//board notation
    string charSpace = " ";
    string boxStr = "|S";
		//boolean to make sure ship placement is valid
    bool invalidDirection = true;
		bool notValid = true;
		bool notPlaced = true;
	

		//determine if the ship is to be placed manually or automatically, if manually get coords from user
		if(placeType == '1'){
			cout << "\nBoat size: " + to_string(this -> size) + "\nWhere would you like to place this boat [eg. F2]: ";
  		cin >> (coords);
    	coords = makeUpper(coords);
		}else{
			//if automatically generate coordinates
			coords = generateCoord(player.board.size());
		}

		//checks lengh of coordinates 
    int length = checkLength(coords);

		//this section converts coordinates into X and Y (similar to shoot)
    if (length == 2) {
      shipX = coords[0];
      shipY = (coords[1] - '0');

    } else if (length == 0) {
			//if coordinates are too short or long, makes user re-enter coordinates
      cout << "Invalid coordinates, please try again\n";
      return this -> placeShip(player, placeType);

    } else if (length == 3) {
			//temporary strings to hold the Y coordinate
      str1 += coords[1];
      str1 += coords[2];
			//temporary string to hold the X coordinate
      str2 += coords[0];
      str2 += coords[1];
			//this checks if the format of the coordinate is letter number number eg, A23
      if (stoi(str1) >= 1 && stoi(str1) <= player.board.size()) {
				//if it is set shipY to int version of str1
        shipY = (stoi(str1));
				//make shipX equal to the first letter of the coord (this gets converted to int later)
        shipX = coords[0];

      } else {
				//if not make shipY equal to the last number in int
        shipY = (coords[2] - '0');
				//make shipX equal to the second part of the coord eg. AB2 = set shipX to B
        shipX = (str2[1]);
      }
    }

		//sets coordsX to a string version of shipX
    string coordsX(1, shipX);

		//loop that converts the X from a char to an int
    for (int i = 0; i < player.board.size(); i++) {
      for (int j = 0; j < player.board[i].size(); j++) {
     
				//checks the size of the board and changes notation accordingly for future comparison
        if (player.board[i].size() > 26) {
          boxStr = "| S";
          charSpace = "  ";

					//Chcks to see if larger X are in the board eg. AB
          if ((charSpace + str2[0] + str2[1]) == player.board[i][j]) {
						//if X found push the y to coordsVect
            coordsVect.push_back(shipY);
						//if X found push the iteration of loop to coordsVect (this will be the X)
            coordsVect.push_back(j);

					//checks to see if X is in the board eg. A
          } else if ((charSpace + coordsX) == player.board[i][j]) {
						//if X found push the y to coordsVect
            coordsVect.push_back(shipY);
						//if X found push the iteration of loop to coordsVect (this will be the X)
            coordsVect.push_back(j);

          }
					//Checks if X is in the board, also identifies if the coordinate is valid or not
        } else if ((charSpace + coordsX) == player.board[i][j]) {
          coordsVect.push_back(shipY);
          coordsVect.push_back(j);
					//checks if coordinate already has a ship on it
					if(player.board[coordsVect[0]][coordsVect[1]] == boxStr){
						if(placeType == '1'){
						cout << "Inavlid coordinate, try again\n";
						}
						//if ship already present wait a second and then make the player enter a different coordinate
						wait(1);
						return this -> placeShip(player, placeType);
					}

        }
      }
    }

		//if manual ship placement asks user for direction, otherwise generates it
		if(placeType == '1'){
			cout << "What direction should it face? [L, R, U, D]: ";
    	cin >> direction;
    	direction = toupper(direction);
		}else{
			//automatically generates direction
			direction = this -> generateDirection(coordsVect, player.board.size());
		}

		//while loop that runs until a valid position is found and the ship is placed
    while (notPlaced) {
      switch (direction) {
      case 'L':
			y = 0;
			//Check collisions with other ships, once no collisions make this valid and places the ship
				while(notValid){
					if(player.board[coordsVect[0]][coordsVect[1] - y] == boxStr){
						if(placeType == '1'){
							cout << "\nInvalid coordinate or direction, try again\n";
						}
						return this -> placeShip(player, placeType);
					}
					
					if((coordsVect[1] - (y + 1)) == (coordsVect[1] - this -> size)){
						notValid = false;
					}
					y++;
				}
			//Set coordinate to ship
        player.board[coordsVect[0]][coordsVect[1] - k] = boxStr;
        if ((coordsVect[1] - (k + 1)) == (coordsVect[1] - this -> size)) {
          notPlaced = false;
        }
        break;
      case 'R':
			y = 0;
				//Check collisions with other ships, once no collisions make this valid and places the ship
				while(notValid){
					if(player.board[coordsVect[0]][coordsVect[1] + y] == boxStr){
						if(placeType == '1'){
							cout << "\nInvalid coordinate or direction, try again\n";
						}
						return this -> placeShip(player, placeType);
					}
					
					if((coordsVect[1] + (y + 1)) == (coordsVect[1] + this -> size)){
						notValid = false;
					}
					y++;
				}
				//Set coordinate to ship
        player.board[coordsVect[0]][coordsVect[1] + k] = boxStr;
        if ((coordsVect[1] + (k + 1)) == (coordsVect[1] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'D':
			y = 0;
				//Check collisions with other ships, once no collisions make this valid and places the ship
				while(notValid){
					if(player.board[coordsVect[0] + y][coordsVect[1]] == boxStr){
						if(placeType == '1'){
							cout << "\nInvalid coordinate or direction, try again\n";
						}
						return this -> placeShip(player, placeType);
					}
					
					if((coordsVect[0] + (y + 1)) == (coordsVect[0] + this -> size)){
						notValid = false;
					}
					y++;
				}
				//Set coordinate to ship
        player.board[coordsVect[0] + k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] + (k + 1)) == (coordsVect[0] + this -> size)) {
          notPlaced = false;
        }
        break;
      case 'U':
			y = 0;
				//Check collisions with other ships, once no collisions make this valid and places the ship
				while(notValid){
					if(player.board[coordsVect[0] - y][coordsVect[1]] == boxStr){
						if(placeType == '1'){
							cout << "\nInvalid coordinate or direction, try again\n";
						}
						return this -> placeShip(player, placeType);
					}
					
					if((coordsVect[0] - (y + 1)) == (coordsVect[0] - this -> size)){
						notValid = false;
					}
					y++;
				}
				//Set coordinate to ship
        player.board[coordsVect[0] - k][coordsVect[1]] = boxStr;
        if ((coordsVect[0] - (k + 1)) == (coordsVect[0] - this -> size)) {
          notPlaced = false;
        }
        break;
      }
      k++;
    }
		//returns updated player with placed ship on their player.board
    return player;
  }
};