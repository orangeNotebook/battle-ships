//player class
class Player {
	//public properties
  public:
    string name;   
    vector<vector<string>> board;
    vector<vector<string>> targetBoard;
		int score = 0;
};

//a function that creates either 1 player and computer or 2 players
vector<Player> createPlayer(int numberOfPlayers){
	//initialising variables
	Player player1;
	Player player2;
	//vector to store the palyers
  vector<Player> players;
	//adding the players to the vector
	players.push_back(player1);
	players.push_back(player2);

	//if 2 players then get 2 names for the players
	if(numberOfPlayers == 2){
		cout << "Player 1 name: ";
		cin >> players[0].name;
		cout << "Player 2 name: ";
		cin >> players[1].name;
	}
	//otherwise get 1 name for hte player and set the other one to computer
	else{
		cout << "Player name: ";
		cin >> players[0].name;
		players[1].name = "Computer";
	}

	//returns the vector of players
	return players;
}

