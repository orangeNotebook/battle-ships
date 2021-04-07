//imports
#include "player-v-player.h"

using namespace std;

//main game loop for player v computer
int playerVComputerGameLoop(vector < Player > players, char developerMode, int winScore) {
  char shootOption;
  bool gameRunning = true;
  int turn = 0;
  int turn2 = 1;
  string targetCoords;

	//while loop that runs until game is over
  while (gameRunning) {
		//checks if its the players turn
    if (turn == 0) {
			//if developermode enabled shows a different target board then if not
      if (developerMode == 'Y') {
				//clears screen and shows target board and player board
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				//tells user how many enemy ship fragments left
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";

				//gets input on automatic fire or manual fire
        cout << "\n1. Fire manually\n2. Fire randomly\n\n0. Quit\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

				//quits the game if the user selects 0
				if(shootOption == '0'){
					Clear();
					return 0;
				}

				//runs shoot and updates players with the updated players
        players = shoot(players, turn, shootOption);

				//clears the screen and prints the updated boards
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      } 
			//else if developer mode is not on
			else {
				//clears the screen and shows the boards (target boards, not enemies board)
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				//tells user how many enemy fragments are left
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
				
				//gets input on automatic fire or manual fire
        cout << "\n1. Fire manually\n2. Fire randomly\n\n0. Quit\n\nPlease choose how you would like to fire: ";
        cin >> shootOption;

				//quits the game if the user selects 0
				if(shootOption == '0'){
					Clear();
					return 0;
				}

				//runs shoot and updates players with the updated player
        players = shoot(players, turn, shootOption);

				//clears the screen and prints the upadted boards
        Clear();
        cout << players[turn].name + "'s turn\n\nTarget board:\n";
        printBoard(players[turn].targetBoard);
        cout << "\n\nYour board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      }

    } 
		//if its the computers turn
		else {
			//if developer mode is on then it follows the same visual style as the person turn, except no options are available, only 'press any key to continue
      if (developerMode == 'Y') {
        Clear();
        cout << players[turn].name + "'s turn (only visible in developer mode)\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nComputers board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        players = shoot(players, turn, 2);
        Clear();
        cout << players[turn].name + "'s turn (only visible in developer mode)\n\nTarget board (developer mode):\n";
        printBoard(players[turn2].board);
        cout << "\n\nComputers board: \n";
        printBoard(players[turn].board);
				cout << "\nEnemy ship fragments left: " + to_string(winScore - players[turn].score) + "\n";
        pressAnyKey();
        Clear();
      } 
			//if developer mode is not on then it automatically shoots and updates players, without printing out anything
			else {
        players = shoot(players, turn, 2);
      }
    }

		//checks if someone has won, if yes quits the game
		if (players[turn].score == winScore) {
      Clear();
      cout << players[turn].name + " wins!\n\n";
      pressAnyKey();
      Clear();
      gameRunning = false;
      return 0;
    }

		//if statement that changes the palyers turn and identifies player and computer
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
	//vectors to store the config data, players, ships and an empty board
  vector < Player > players = createPlayer(1);
  vector < int > Data = readFile();
  vector < Ship > ships = createShips(Data);
  vector < vector < string >> emptyBoard = createBoard(Data[0], Data[1]);

	//variables to store coords, what type of ship placement the user wants and the win score	
  char placeChoice;
  char developerMode;
	int winScore;

	//Asks user if they would like to see developer mode
  cout << "Would you like to access developer mode (see computers ships and turn)\n\n[Y/N]: ";
  cin >> developerMode;
	//converts input to upper case
  developerMode = toupper(developerMode);

	//loops through palyers and places boats
  for (int i = 0; i < players.size(); i++) {
    char choice;
		//sets the players board and target board to an empty board
    players[i].board = emptyBoard;
    players[i].targetBoard = emptyBoard;
    Clear();

		//if its the players turn then asks if they want to palce their ships manually or automatically
    if (i == 0) {
      cout << players[i].name + "'s turn\n\n1. Place your boats manually\n2. Place your boats automatically\n\n0. Quit\n\nPlease choose a way to set your board up: ";

      cin >> placeChoice;

			//if they chose to quit quits
			if(placeChoice == '0'){
				Clear();
				return 0;
			}

			//if chose manual then prints board and ship size, followed by placeShips method with manual placeChoice
      if (placeChoice == '1') {
				winScore = 0; //winScore generated here
				//goes through all of the ships
        for (int j = 0; j < ships.size(); j++) {
					winScore += ships[j].size;
          Clear();
          cout << players[i].name + "'s Board: \n";
          printBoard(players[i].board);
          cout << "\n";
          players[i] = ships[j].placeShip(players[i], placeChoice);
          cout << "\n";
        }
      } 
			//if chose automatic
			else {
				winScore = 0; //win score gen here
				//goes through all of the ships and runs placeShip with automatic placeCHoice
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

			//asks user if they are happy with their board, if not reruns loop
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
		//Bot place ships here
		else {
			//if developer mode is on then we can see where the boats are being placed, just like automatic place for player
      if (developerMode == 'Y') {
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
					printBoard(players[i].board);
					cout << "\nGenerating ship placement, please wait\n";
          players[i] = ships[j].placeShip(players[i], '2');
					Clear();
					cout << players[i].name + "'s Board: \n";
					printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
        }
				//no confirmation of placement, just press any key to continue for bot
        pressAnyKey();
      } 
			//if dev mode is off then we cant see placement of ships
			else {
        for (int j = 0; j < ships.size(); j++) {
          Clear();
          cout << players[i].name + "'s Board: \n";
          // printBoard(players[i].board);
          cout << "\nGenerating ship placement, please wait\n";
          cout << "\n";
          players[i] = ships[j].placeShip(players[i], '2');
          cout << "\n";
        }
      }
    }

  }

	//runs game loop for player vs computer with the players vector, developerMode choice and score needed to win
  playerVComputerGameLoop(players, developerMode, winScore);

	//returns 0 to end
  return 0;
}