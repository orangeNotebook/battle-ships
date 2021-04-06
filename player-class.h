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

#ifndef INCLUDED_A_H
#define INCLUDED_A_H

class Player {
  public:
    string name;   
    vector<vector<string>> board;
    vector<vector<string>> targetBoard;
		int score = 0;
};

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

#endif