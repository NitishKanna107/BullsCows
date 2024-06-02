/*
Last updated: 2/6/2024
Author: Nitish Kanna
*/

#include"std_lib_facilities.h"

bool bullCow(std::string guess);
std::string word = "";

int main()
{
	try {
		bool newGame = true;
		std::cout << "Welcome to Bulls and Cows" << '\n';
		std::cout << "Guess a four digit number with no single digit repeated more than once\n"
			"If you guess the right letter in the right place then you score a bull\n"
			"If you guess the right letter in the wrong place then you score a cow\n"
			"Use only uppercase letters\n"
			"Score 4 bulls to win the game\n\n"
			"Enter a character to start playing$";

		while(std::cin) {
			std::string guess;
			std::cin >> guess;

			if (guess == "?" && !newGame) {
				std::cout << word << '\n';
				newGame = true;
			}

			if (!newGame) newGame = bullCow(guess);

			if (newGame) {
				int seed;
				word.clear();

				std::cout << "Seed (new game)$ ";
				std::cin >> seed;

				seed_randint(seed);
				for (int i = 0; i < 4; ++i) word += 'A' + randint(25);

				newGame = false;
				std::cout << "You can start guessing now!" << '\n';
			}
		}
	}
	catch (runtime_error& err) {
		std::cerr << "#" << err.what() << '\n';
		keep_window_open(".");
		return -1;
	}
}

bool bullCow(std::string guess)
{
	if(guess.length() != 4) 
		throw runtime_error("bullCow() accepts only a four letter word");

	int bull = 0;
	int cow = 0;
	bool gameOver = false;

	for (char x : guess) {
		if (x < 'A' || x > 'Z') throw runtime_error("guess can contain only uppercase letters");

		int count = 0;
		for (char y : guess) if (x == y) ++count;

		if (count > 1) {
			std::cout << "You ain't ever gonna win by guessing like this!!" << '\n';
			return gameOver;
		}
	}

	for (int i = 0; i < word.length(); ++i) {
		for (int j = 0; j < guess.length(); ++j) {
			if (word[i] == guess[j]) {
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