#ifndef MAIN_HH
#define MAIN_HH

#include <iostream>
#include <string>
#include "BullCowGame.hh"

void printBullsAndCows(EvaluationResponse resp)
{
	std::cout << "Bulls: " << resp.bulls << " - Cows: " << resp.cows << std::endl;
}

void printGuessStatus(GuessStatus status, size_t isogramLength)
{
	std::cout << "Guess invalid";
	switch(status)
	{
		case GuessStatus::LengthMismatch:
			std::cout << " - Guess length is not " << isogramLength << "!\n";
			break;
		case GuessStatus::NotAllLetters:
			std::cout << " - Guess is not only letters!\n";
			break;
		case GuessStatus::NotIsogram:
			std::cout << " - Guess is not an isogram!\n";
			break;
		case GuessStatus::NotLowerCase:
			std::cout << " - Guess is not all lowercase!\n";
			break;
		default:
			std::cout << "!\n";
			break;
	}
}

void printIntroduction(BullCowGame game, bool playingAgain)
{
	std::ostringstream os;
	if(playingAgain)
		os << std::endl;

	os << "Welcome to Bulls and Cows, a fun word game.\n\n"
		<< "          }   {       ___ \n"
		<< "          (o o)      (o o)\n"
		<< "   /-------\\ /        \\ /-------\\ \n"
		<< "  / | BULL |O          O| COW  | \\ \n"
		<< " *  |-,--- |            |------|  * \n"
		<< "    ^      ^            ^       ^ \n"
		<< "\nCan you guess which "
		<< game.GetIsogramLength()
		<< " letter isogram I've got in mind?\n";

	std::cout << os.str();
}

void printLostGame()
{
	std::cout << "\nYou've failed to guess the correct isogram!\n";
}

void printWonGame()
{
	std::cout << "\nYou've guessed the correct isogram!\n";
}

bool shouldPlayAgain()
{
	std::cout << "\nDo you want to play again (y/n)? ";
	std::string again = "";
	std::getline(std::cin, again);

	return again[0] == 'y' || again[0] == 'Y';
}

std::string getGuess(BullCowGame game)
{
	std::string guess = "";
	GuessStatus status = GuessStatus::Invalid;
	do
	{
		std::cout << "\nAttempt " << game.GetCurrentAttempt() << "/" << game.GetMaxAttempts() << " > ";
		std::getline(std::cin, guess);

		status = game.ValidateGuess(guess);
		if(status != GuessStatus::Ok)
			printGuessStatus(status, game.GetIsogramLength());
	} while(status != GuessStatus::Ok);

	return guess;
}

void playGame(BullCowGame game)
{
	game.Reset();

	while(game.GetCurrentAttempt() <= game.GetMaxAttempts())
	{
		std::string guess = getGuess(game);
		printBullsAndCows(game.EvaluateGuess(guess));

		if(game.IsGameWon())
		{
			printWonGame();
			break;
		}
	}

	if(!game.IsGameWon())
		printLostGame();
}

#endif //MAIN_HH
