#include <iostream>//defines the standard devices cin, cout, clog, ceer; for more info see http://www.cplusplus.com/reference/iostream/
#include <string> //defines string types and conventions including begin & end iterator; for more info see http://www.cplusplus.com/reference/string/
#include <algorithm>//defines a collection of ranged functions; for more info see http://www.cplusplus.com/reference/algorithm/
#include <random>//defines random number generation facilities; for more info see http://wwww.cplusplus.com/reference/random/
#include <ctime>//declares a set of functions, macros and types to work with date and time information e.g. the time() function is used to get the current time

//include default source files for daily primer challenges
// #include "player-v-player.h"
#include "player-v-computer.h"


//function declarations:
//tell the compiler about the function; required if function isn't compiled prior to reference
void menu(void);

//fn to clear once primers are exited
// void Clear()
// {
//     cout << "\x1B[2J\x1B[H";
// }

//this is the 
int main() {
	menu();
	return 0; //return value (0) typically used to indicate a 'no error' status
}

void menu(void) {
	std::string spacing = "                      ";
	std:: string topBorBorder = "|--------------------------------|";
	int choice = -1; //declare and initialise an integer type variable
  Clear();
	do { //set up a continuous loop
		std::cout <<"                                      |\n";
		std::cout <<"                                      ---\n";
		std::cout <<"                                     / | [\n";
		std::cout <<"                              !      | |||\n";
		std::cout <<"                            _/|     _/|-++'\n";
		std::cout <<"                        +  +--|    |--|--|_ |-\n";
		std::cout <<"                     { /|__|  |/___|  |--- |||__/\n";
		std::cout <<"                    +---------------___[}-_===_.'____                  \n";
		std::cout <<"                ____`-' ||___-{]_| _[}-  |     |_[___==--                  _\n";
		std::cout <<" __..._____--==/___]_|__|_____________________________[___==--____,------' .7\n";
		std::cout <<"|                                                                      ADA  /\n";
		std::cout <<" |_________________________________________________________________________|\n";
		std::cout << "\n" + spacing + "" + topBorBorder + "\n" + spacing + "|Advanced Programming - Ada Ships|\n"; 
		std::cout << spacing + "|                                |\n";
		std::cout << spacing + "|\t1. Player vs Computer          |\n";
		std::cout << spacing + "|\t2. Player vs Player            |\n";
		std::cout << spacing + "|                                |\n" + spacing + "|\t0. Quit                        |\n";

		std::cout << spacing +  topBorBorder + "\n" + spacing + "\n" + spacing + "  Please choose a game mode: ";
		std::cin >> choice;

		switch(choice) {
			case 1: Clear(); playerVComputer(); break;
			case 2: Clear(); playerVPlayer(); break;
			case 0: std::cout << "Exiting"; break;
			default:
				std::cout << "\n'" << choice << "' Is an invalid option  - please try again.";
				break;
		}
	} while(choice != 0);
	std::cout << " - Done\n\n";
}