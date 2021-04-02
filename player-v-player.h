//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>


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

		vector<int> place(vector<vector<string>> board){
			vector<int> coordsVect;
			int alphabetToInt = 0;
			string coords;

			cout << "Boat size: " + to_string(this->size) + "\nWhere would you like to place this boat: ";
			cin >> coords;

			char c = coords[0];

			string coordsX(1,coords[0]);

			for(int i = 0; i < board.size(); i++){
				for(int j = 0; j < board[i].size(); j++){
					//cout << "Comparing board: '" + board[i][j] + "' to : '" + (" " + (coords[0])) + "'\n";
					if((" " + coordsX) == board[i][j]){
						coordsVect.push_back((coords[1] - '0'));
						coordsVect.push_back(j);
					}
				}
			}
			
			return coordsVect;
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
		players[i].board = emptyBoard;
		players[i].targetBoard = emptyBoard;

		
		
		for(int j = 0; j < ships.size(); j++){
			// Clear();
			cout << players[i].name + "'s Board: \n";
			printBoard(players[i].board);
			cout << "\n";
			vector<int> coords = ships[j].place(players[i].board);
			players[i].board[coords[0]][coords[1]] = "|S";
			cout << "\n";
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
