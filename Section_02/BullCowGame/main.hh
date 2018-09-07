#ifndef MAIN_HH
#define MAIN_HH

#include <iostream>
#include <string>
#include "BullCowGame.hh"

std::string getGuess(BullCowGame game)
{
	std::cout << "\nAttempt " << game.GetCurrentAttempt() << " > ";
	std::string guess = "";
	std::getline(std::cin, guess);

	return guess;
}

void repeatBackGuess(std::string guess)
{
	std::cout << "\nYou guessed: " << guess << std::endl;
}

bool shouldPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	std::string again = "";
	std::getline(std::cin, again);

	return again[0] == 'y' || again[0] == 'Y';
}

void playGame(BullCowGame game)
{
	game.Reset();

	std::string guess = "";
	for(int i = 0; i < game.GetMaxAttempts(); i++)
	{
		guess = getGuess(game);
		game.ValidateGuess(guess);
		repeatBackGuess(guess);
	}
}

#endif //MAIN_HH
