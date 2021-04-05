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


#include "board-creation.h"
#include "read-config.h"

using namespace std;

void Clear()
{
    cout << "\x1B[2J\x1B[H";
}

class Player {
  public:
    string name;   
    vector<vector<string>> board;
    vector<vector<string>> targetBoard;
};

class Ship {
  public:
    string name;   
    int size;


		int checkLength(string coords){
			if(coords.size() == 1){
				return 0;
			}else if(coords.size() == 2){
				return 2;
			}else if(coords.size() == 3){
				return 3;
			}else if(coords.size() == 4){
				return 4;
			}
			return 0;
		}

		string generateCoord(int size){
			string coords = "";
			string alphabetArray[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
			int number, letter;
			time_t nTime;

			srand((unsigned) time(&nTime));
			number = ((rand() % size) + 1);

			if(size <= 26){
				srand((unsigned) time(&nTime));
				letter = (rand() % size);
				coords += alphabetArray[letter] + to_string(number);
			}else{
				srand((unsigned) time(&nTime));
				letter = (rand() % 26);
				coords += "A" + alphabetArray[letter] + to_string(number);
			}

			return coords;
		}

		char generateDirection(){
			char directionArray[] = {'L', 'R', 'U', 'D'};
			int number, letter;
			time_t nTime;

			srand((unsigned) time(&nTime));
			number = ((rand() % 4) + 1);

			return directionArray[number];
		}

		Player randomPlacement(Player player){
			

		}
//
		Player placeShip(Player player){
			vector<int> coordsVect;
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
			string coord;

			coord = generateCoord(player.board.size());

			int length = checkLength(coord);

			if(length == 2){
				shipX = coords[0];
				shipY = (coords[1] - '0');

			}else if(length == 0){
					cout << "Invalid coordinates, please try again\n";
					return this->placeShip(player);

			}else if(length == 3){
					str1 += coords[1];
					str1 += coords[2];

					str2 += coords[0];
					str2 += coords[1];
					if(stoi(str1) >=1 && stoi(str1) <= player.board.size()){
						shipY = (stoi(str1));
						shipX = coords[0];

					}else{
						shipY = (coords[2] - '0');
						shipX = (str2[1]);
					} 
				}
			

	

			string coordsX(1,shipX);

			for(int i = 0; i < player.board.size(); i++){
				for(int j = 0; j < player.board[i].size(); j++){
					//cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";
					if(player.board[i].size() > 26){			
   				boxStr = "| S";
  				charSpace = "  ";

				
						if((charSpace + str2[0] + str2[1]) == player.board[i][j]){
							coordsVect.push_back(shipY);
							coordsVect.push_back(j);
							cout << to_string(coordsVect[0]);
							cout << to_string(coordsVect[1]);
						}else if((charSpace + coordsX) == player.board[i][j]){
							coordsVect.push_back(shipY);
							coordsVect.push_back(j);
							cout << to_string(coordsVect[0]);
							cout << to_string(coordsVect[1]);
						}
					}
					else if((charSpace + coordsX) == player.board[i][j]){
						coordsVect.push_back(shipY);
						coordsVect.push_back(j);
						cout << to_string(coordsVect[0]);
						cout << to_string(coordsVect[1]);
					}
				}
			}

				while(notPlaced){

				direction = this->generateDirection();
				switch(direction){
					case 'L':
						player.board[coordsVect[0]][coordsVect[1] - k] = boxStr;
						if ((coordsVect[1] - (k+1)) == (coordsVect[1] - this->size)){ notPlaced = false; }
						break;
					case 'R':
						player.board[coordsVect[0]][coordsVect[1] + k] = boxStr;
						if ((coordsVect[1] + (k+1)) == (coordsVect[1] + this->size)){ notPlaced = false; }
						break;
					case 'D':
						player.board[coordsVect[0] + k][coordsVect[1]] = boxStr;
						if ((coordsVect[0] + (k+1)) == (coordsVect[0] + this->size)){ notPlaced = false; }
						break;
					case 'U':
						player.board[coordsVect[0] - k][coordsVect[1]] = boxStr;
						if ((coordsVect[0] - (k+1)) == (coordsVect[0] - this->size)){ notPlaced = false; }
						break;
				}
				k++;
			}

			return player;
			}
		
//old one
		Player place(Player player){
			vector<int> coordsVect;
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

			cout << "1. Place your boats\n2. Place boats automatically";

			cin >> placeOption;

			if(placeOption == '2'){
				return this->placeShip(player);
			}

			cout << "\nBoat size: " + to_string(this->size) + "\nWhere would you like to place this boat [eg. F2]: ";
			cin >> (coords);

			int length = checkLength(coords);

			if(length == 2){
				shipX = coords[0];
				shipY = (coords[1] - '0');

			}else if(length == 0){
					cout << "Invalid coordinates, please try again\n";
					return this->place(player);

			}else if(length == 3){
					str1 += coords[1];
					str1 += coords[2];

					str2 += coords[0];
					str2 += coords[1];
					if(stoi(str1) >=1 && stoi(str1) <= player.board.size()){
						shipY = (stoi(str1));
						shipX = coords[0];

					}else{
						shipY = (coords[2] - '0');
						shipX = (str2[1]);
					} 
				}
			

	

			string coordsX(1,shipX);

			for(int i = 0; i < player.board.size(); i++){
				for(int j = 0; j < player.board[i].size(); j++){
					//cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";
					if(player.board[i].size() > 26){			
   				boxStr = "| S";
  				charSpace = "  ";

				
						if((charSpace + str2[0] + str2[1]) == player.board[i][j]){
							coordsVect.push_back(shipY);
							coordsVect.push_back(j);
							cout << to_string(coordsVect[0]);
							cout << to_string(coordsVect[1]);
						}else if((charSpace + coordsX) == player.board[i][j]){
							coordsVect.push_back(shipY);
							coordsVect.push_back(j);
							cout << to_string(coordsVect[0]);
							cout << to_string(coordsVect[1]);
						}
					}
					else if((charSpace + coordsX) == player.board[i][j]){
						coordsVect.push_back(shipY);
						coordsVect.push_back(j);
						cout << to_string(coordsVect[0]);
						cout << to_string(coordsVect[1]);
					}
				}
			}

			cout << "What direction should it face? [L, R, U, D]: ";
			cin >> direction;

			while(notPlaced){
				
				switch(direction){
					case 'L':
						player.board[coordsVect[0]][coordsVect[1] - k] = boxStr;
						if ((coordsVect[1] - (k+1)) == (coordsVect[1] - this->size)){ notPlaced = false; }
						break;
					case 'R':
						player.board[coordsVect[0]][coordsVect[1] + k] = boxStr;
						if ((coordsVect[1] + (k+1)) == (coordsVect[1] + this->size)){ notPlaced = false; }
						break;
					case 'D':
						player.board[coordsVect[0] + k][coordsVect[1]] = boxStr;
						if ((coordsVect[0] + (k+1)) == (coordsVect[0] + this->size)){ notPlaced = false; }
						break;
					case 'U':
						player.board[coordsVect[0] - k][coordsVect[1]] = boxStr;
						if ((coordsVect[0] - (k+1)) == (coordsVect[0] - this->size)){ notPlaced = false; }
						break;
				}
				k++;
			}

			return player;
		}
};

void pressAnyKey(){
//codes here
cout << "Press any key to continue...";
cin.ignore();
cin.get();
}


void printBoard(vector<vector<string>> Board){
  for(int i=0; i<Board.size(); i++){
        for(int j=0; j<Board[1].size(); j++){
          cout<< Board[i][j] << "";
        }
        cout << endl;
      }
}

vector<Player> createPlayer(int numberOfPlayers){
	Player player1;
	Player player2;
  vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);

	if(numberOfPlayers == 2){
		cout << "Player 1 name: ";
		cin >> players[0].name;
		cout << "Player 2 name: ";
		cin >> players[1].name;
	}else{
		cout << "Player name: ";
		cin >> players[0].name;
		players[1].name = "Computer";
	}

	return players;
}

vector<Ship> createShips(vector<int> Data){
	Ship ship;
	vector<Ship> ships;
	for(int i = 0; i < (Data.size() - 2) ; i++){
		ship.size = Data[i+2];
		ship.name = ("Ship " + to_string(i+1));
		ships.push_back(ship);
	}
	return ships;
}

vector<Player> shoot(vector<Player> players, int turn){
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

	cout << "\nChoose where to shoot [eg. F2]: ";
		cin >> coords;

	if(turn == 0){
		targetPlayer = 1;
	}else{
		targetPlayer = 0;
	}

	if(coords.size() == 2){
				targetX = coords[0];
				targetY = (coords[1] - '0');

			}else if(coords.size() == 0 || coords.size() >= 4){
					cout << "Invalid coordinates, please try again\n";
					return shoot(players, turn);

			}else if(coords.size() == 3){
					str1 += coords[1];
					str1 += coords[2];

					str2 += coords[0];
					str2 += coords[1];
					if(stoi(str1) >=1 && stoi(str1) <= players[targetPlayer].board.size()){
						targetY = (stoi(str1));
						targetX = coords[0];

					}else{
						targetY = (coords[2] - '0');
						targetX = (str2[1]);
					} 
				}
			
			string coordsX(1,targetX);
	

	for(int i = 0; i < players[targetPlayer].board.size(); i++){
		if(players[targetPlayer].board[i].size() > 26){			
		checkShip = "| S";
		checkEmpty = "|  ";
		hitMarker = "| H";
		missMarker = "| M";
		charSpace = "  ";
	}
				for(int j = 0; j < players[targetPlayer].board[i].size(); j++){

					if((charSpace + coordsX) == players[targetPlayer].board[i][j]){
						intTargetX = j;
					}

				}
	}		
	if(players[targetPlayer].board[targetY][intTargetX] == checkShip){
		players[targetPlayer].board[targetY][intTargetX] = hitMarker;
		players[turn].targetBoard[targetY][intTargetX] = hitMarker;
	}else if(players[targetPlayer].board[targetY][intTargetX] == checkEmpty){
		players[targetPlayer].board[targetY][intTargetX] = missMarker;
		players[turn].targetBoard[targetY][intTargetX] = missMarker;
	}

	return players;
}

int gameLoop(vector<Player> players){
	bool gameRunning = true;
	int turn = 0;
	string targetCoords;

	while(gameRunning){
		Clear();
		cout << players[turn].name + "'s turn\n\nTarget board:\n";
		printBoard(players[turn].targetBoard);
		cout << "\n\nYour board: \n";
		printBoard(players[turn].board);
		players = shoot(players, turn);
		Clear();
		cout << players[turn].name + "'s turn\n\nTarget board:\n";
		printBoard(players[turn].targetBoard);
		cout << "\n\nYour board: \n";
		printBoard(players[turn].board);
		pressAnyKey();
		Clear();
		cout << "Please hand the game to the next player\n\n";
		pressAnyKey();
		Clear();

		if(turn == 0){
			turn = 1;
		}else{
			turn = 0;
		}
	}
	return 0;
}

//main function
int playerVPlayer(){

	vector<Player> players = createPlayer(2);

	vector<int> Data = readFile();

	vector<Ship> ships = createShips(Data);

	vector<vector<string>> emptyBoard = createBoard(Data[0], Data[1]);


	cout << "Welcome "+ players[0].name + " and " + players[1].name + "\n";

	for(int i = 0; i < players.size(); i++){
		char choice;
		players[i].board = emptyBoard;
		players[i].targetBoard = emptyBoard;

		
		
		for(int j = 0; j < ships.size(); j++){
			Clear();
			cout << players[i].name + "'s Board: \n";
			printBoard(players[i].board);
			cout << "\n";
			players[i] = ships[j].place(players[i]);
			cout << "\n";
		}
		Clear();
		cout << players[i].name + "'s Board: \n";
		printBoard(players[i].board);
		cout << "\nAre you happy with your board layout? [Y, N]: ";
		cin >> choice;
		if(choice == 'N'){
			players[i].board = emptyBoard;
			i--;
		}

	}
	gameLoop(players);

	

// for(int i = 0; i < players.size(); i++){
// 		cout << players[i].name + "'s Target Board: \n";
// 		printBoard(players[i].targetBoard);
// 		cout << players[i].name + "'s Board: \n";
// 		printBoard(players[i].board);
// 		cout << "\n\n\n";
// 	}

// 	players[0].targetBoard[2][4] = "|M";
// 	printBoard(players[0].targetBoard);

// 	Ship ship1;
// 	ship1.size = 4;
// 	ship1.placeShip(players[0].board);

  return 0;
}
