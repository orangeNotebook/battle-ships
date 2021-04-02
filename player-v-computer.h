//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "board-creation.h"
#include "read-config.h"

using namespace std;

void printBoard(vector<vector<string>> Board){
  for(int i=0; i<Board.size(); i++){
        for(int j=0; j<Board[1].size(); j++){
          cout<< Board[i][j] << "";
        }
        cout << endl;
      }
}
//main function
int playerVComputer(){
  
vector<int> Data = readFile();

vector<vector<string>> Board = createBoard(Data[0], Data[1]);

printBoard(Board);

  return 0;
}
