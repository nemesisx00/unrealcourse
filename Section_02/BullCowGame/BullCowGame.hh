#ifndef BULLCOWGAME_HH
#define BULLCOWGAME_HH

#include <iostream>
#include <sstream>
#include <string>

class BullCowGame
{
public:
	BullCowGame(int, int);

	int GetCurrentAttempt() const;
	int GetMaxAttempts() const;
	bool IsGameWon() const;
	std::string GetIntroduction() const;

	void Reset();
	bool ValidateGuess(std::string);

private:
	const static std::string Introduction1;
	const static std::string Introduction2;

	bool won;
	int currentAttempt;
	int maxAttempts;
	int wordLength;
	std::string isogram;

	bool IsIsogram(std::string);
};

#endif // !BULLCOWGAME_HH
