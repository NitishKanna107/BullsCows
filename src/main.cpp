/*
Last updated: 29/5/2024
Author: Nitish Kanna
*/

#include"std_lib_facilities.h"

bool bullCow(int guess);
vector<int>num;

int main()
{
	try {
		bool newGame = true;
		std::cout << "Welcome to Bulls and Cows" << '\n';
		std::cout << "Guess a four digit number with no single digit repeated more than once\n"
					 "If you guess the right digit in the right place then you score a bull\n"
					 "If you guess the right digit in the wrong place then you score a cow\n"
					 "Score 4 bulls to win the game\n\n";
		std::cout << "Enter any number to start playing$ ";

		for (int guess; std::cin >> guess;) {
			if (guess == -1) {
				for (int i : num) std::cout << i;
				std::cout << '\n';
				newGame = true;
			}

			if (!newGame) newGame = bullCow(guess);
			
			if(newGame) {
				int seed;
				std::cout << "Seed (new game)$ ";
				std::cin >> seed;

				seed_randint(seed);
				for (int i = 0; i < 4; i++) num.push_back(randint(9));

				newGame = false;
				std::cout << "You can start guessing now!" << '\n';
			}
		}

		if (!std::cin)
			throw runtime_error("Bad input to main()");
	}
	catch (runtime_error& err) {
		std::cerr << "#" << err.what() << '\n';
		keep_window_open(".");
		return -1;
	}
}

bool bullCow(int guess)
{
	if (guess > 9999 || guess < 1000)
		throw runtime_error("bullCow() accepts only a four digit number");

	vector<int>input;

	int bull = 0;
	int cow = 0;
	bool gameOver = false;

	for(int i = 3; i >= 0; --i) {
		int tenp = pow(10, i);
		int n = guess / tenp;
		guess = guess % tenp;
		
		for (int x : input) {
			if (n == x) {
				std::cout << "You ain't ever gonna win by guessing like this!!" << '\n';
				return gameOver;
			}
		}
		input.push_back(n);
	}

	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < num.size(); j++) {
			if (input[i] == num[j]) {
				if (i == j)
					++bull;
				else
					++cow;
			}
		}
	}

	std::cout << bull << " bull " << cow << " cow\n";	
	if (bull == 4) {
		gameOver = true;
		std::cout << "ahh!! You found me" << '\n';
	}

	return gameOver;
}