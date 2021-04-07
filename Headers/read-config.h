//importing
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

//class to interpret CSV files and allow the user to access each row
class CSVRow{
  public:
    //defining variables to hold row string
    string m_line;
    vector<int> m_data;

    //operator overloading to allow to get a row via classInstance[rowNumber]
    string operator [] (int index) const{
      return string(&m_line[m_data[index] + 1], m_data[index + 1] -  (m_data[index] + 1));
    }

    //a method that returns the size of a field
    int size() const{
      return m_data.size() - 1;
    }

    //a method to get the next field in the column
    void readNextRow(istream& str){
      //defining var (this is for the position of ',' characters)
      int pos = 0;
      //gets the current row
      getline(str, m_line);

      //removes all elements from my data vector
      m_data.clear();
      m_data.emplace_back(-1);

      //looks for ',', if found returns the pos (index of where it is in the row)
      while((pos = m_line.find(',', pos)) != string::npos)
      {
        m_data.emplace_back(pos);
        ++pos;
      }
      // This checks for a trailing comma with no data after it.
      pos   = m_line.size();
      m_data.emplace_back(pos);
    }
};

//extraction operator, takes in the file and CSVRow instance, used to move on to the next row in a file
istream& operator >> (istream& str, CSVRow& data){
  data.readNextRow(str);
  return str;
}   

//split function
vector<string> split(string strToSplit, char delimeter){
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

//Function to display the array 
void display(int** a, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

vector<int> readFile(){
  //initialising class
  CSVRow row;
  int boardX;
  int boardY;
  vector<int> Data;

  //getting file
  ifstream file("adaship_config.csv");

  //while loop that iterates through each row 
  while(file >> row)
  {
		//checks for board
    if(row[0] == "Board"){    
			//splits board at 'x' 
      vector board = split(row[1], 'x');

			//adds the board size to Data vector for future use
      Data.push_back(stoi(board[0]));
      Data.push_back(stoi(board[1]));

    }
		//checks for boats
		else if(row[0] == "Boat"){

			//adds boats to Data vector for future use
      Data.push_back(stoi(row[2]));
    }
   
  }
	//returns the data vector, first 2 indexes are board size everything after are boat sizes eg. for 10x8 grid with a 5 and 4 size boat -> {10,8,5,4}
  return Data;
}