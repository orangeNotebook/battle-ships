//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>


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

		Player place(Player player){
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
			string boxStr = " |";

			cout << "Boat size: " + to_string(this->size) + "\nWhere would you like to place this boat [eg. F2]: ";
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
					if(stoi(str1) >=1 && stoi(str1)  <=player.board.size()){
						shipY = (stoi(str1));
						shipX = coords[0];

					}else{
						shipY = (coords[2] - '0');
						// shipX = (str2);
					} 
				}
			

	

			string coordsX(1,shipX);

			for(int i = 0; i < player.board.size(); i++){
				for(int j = 0; j < player.board[i].size(); j++){
					//cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";
					if(player.board[i].size() > 26){			
   				boxStr = "| S";
  				charSpace = "  ";
					}
					if((charSpace + coordsX) == player.board[i][j]){
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
