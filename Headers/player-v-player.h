//importing
#include<unistd.h>
#include "read-config.h"
#include "shoot.h"

using namespace std;

//Function that creates all of the ships from provided data
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

//Main game loop
int playerVPlayerGameLoop(vector < Player > players, int winScore) {
  bool gameRunning = true;
  int turn = 0;
  string targetCoords;
	char shootOption;

	//while loop that runs until game is over
  while (gameRunning) {
		//clears the screen
    Clear();
		//prints out the target board and the players board
    cout << players[turn].name + "'s turn\n\nTarget board:\n";
    printBoard(players[turn].targetBoard);
    cout << "\n\nYour board: \n";
    printBoard(players[turn].board);
		//prints out how many enemy ship fragments are left
		cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";

		//gets the shootOption to determine if the user wants to shoot automatically or manually
 		cout << "\n1. Fire manually\n2. Fire randomly\n\n0. Quit\n\nPlease choose how you would like to fire: ";
    cin >> shootOption;

		//returns 0 if the user wants to quit
		if(shootOption == '0'){
			Clear();
			return 0;
		}

		//otherwise runs shoot and sets the players to the updated players
    players = shoot(players, turn, shootOption);

		//clears the board
    Clear();
		//prints out the updated target board and player board
    cout << players[turn].name + "'s turn\n\nTarget board:\n";
    printBoard(players[turn].targetBoard);
    cout << "\n\nYour board: \n";
    printBoard(players[turn].board);
		//prints out updated enemy ship fragments
		cout << "\nShip fragments left: " + to_string(winScore - players[turn].score) + "\n";

		//checks if the player has won the game
    if (players[turn].score == winScore) {
			//if player has won clears the screen and informs the palyer, then stops the game running and retuns 0 to exit
      Clear();
      cout << players[turn].name + " wins!\n\n";
      pressAnyKey();
      Clear();
      gameRunning = false;
      return 0;
    }

		//menu to hand over to other player without the first player seeing their board
    pressAnyKey();
    Clear();
    cout << "Please hand the game to the next player\n\n";
    pressAnyKey();
    Clear();

		//if statement that changes who's turn it currently is
    if (turn == 0) {
      turn = 1;
    } else {
      turn = 0;
    }
  }
	//once game is over returns 0
  return 0;
}


//main function
int playerVPlayer() {
	//vectors to store the config data, players, ships and an empty board
  vector < Player > players = createPlayer(2);
  vector < int > Data = readFile();
  vector < Ship > ships = createShips(Data);
  vector < vector < string >> emptyBoard = createBoard(Data[0], Data[1]);

	//variables to store coords, what type of ship placement the user wants and the win score
	string coords = "";
  char placeChoice;
	char choice; //happy with ship or not
	int winScore = 0;

	//loops through palyers and places boats
  for (int i = 0; i < players.size(); i++) {
    //sets the players board and target board to an empty board
    players[i].board = emptyBoard;
    players[i].targetBoard = emptyBoard;
    Clear();

		//choice for placing ships automatically or manually
    cout << players[i].name + "'s turn\n\n1. Place your boats manually\n2. Place your boats automatically\n\n0. Quit\n\nPlease choose a way to set your board up: ";
    cin >> placeChoice;

		//if user wants to quit return 0
		if(placeChoice == '0'){
			Clear();
			return 0;
		}

		//if choice is manual then go through each boat with palcechoice 2
    if (placeChoice == '1') {
			winScore = 0;
      for (int j = 0; j < ships.size(); j++) {
        winScore += ships[j].size; //win score gets set here
        Clear();
				//prints users board
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

		//clears the screen, shows user the board and asks if they are happy with the layout, if not resets the place loop
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

	//runs the game loop, parsing players and the score needed to win
  playerVPlayerGameLoop(players, winScore);

  return 0;
}