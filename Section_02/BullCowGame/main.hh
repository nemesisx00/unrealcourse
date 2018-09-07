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

void printBullsAndCows(EvaluationResponse resp)
{
	std::cout << "\nBulls: " << resp.bulls << " - Cows: " << resp.cows << std::endl;
}

void printGuess(std::string guess)
{
	std::cout << "You guessed: " << guess << std::endl;
}

void printGuessStatus(GuessStatus status)
{
	std::cout << "\nGuess invalid";
	switch(status)
	{
		case GuessStatus::NotLongEnough:
			std::cout << " - Guess is not long enough!\n";
			break;
		case GuessStatus::NotIsogram:
			std::cout << " - Guess is not an isogram!\n";
			break;
		default:
			std::cout << "!\n";
			break;
	}
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

void playGame(BullCowGame game)
{
	game.Reset();

	std::string guess = "";
	do
	{
		guess = getGuess(game);
		GuessStatus wordStatus = game.ValidateGuess(guess);
		if(wordStatus == GuessStatus::Ok)
		{
			printBullsAndCows(game.EvaluateGuess(guess));
			printGuess(guess);

			if(game.IsGameWon())
			{
				printWonGame();
				break;
			}
		}
		else
			printGuessStatus(wordStatus);
	} while(game.GetCurrentAttempt() < game.GetMaxAttempts());

	if(!game.IsGameWon())
		printLostGame();
}

#endif //MAIN_HH
