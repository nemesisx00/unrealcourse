#ifndef BULLCOWGAME_HH
#define BULLCOWGAME_HH

#include <iostream>
#include <sstream>
#include <string>
#include "EvaluationResponse.hh"

enum class GuessStatus
{
	Ok,
	NotIsogram,
	NotLongEnough,
	NotLowerCase
};

class BullCowGame
{
public:
	BullCowGame(size_t);

	size_t GetCurrentAttempt() const;
	size_t GetIsogramLength() const;
	size_t GetMaxAttempts() const;
	std::string GetIntroduction() const;

	bool IsGameWon() const;
	GuessStatus ValidateGuess(std::string) const;

	void Reset();
	EvaluationResponse EvaluateGuess(std::string);

private:
	const static std::string Introduction1;
	const static std::string Introduction2;

	bool won;
	size_t currentAttempt;
	size_t maxAttempts;
	size_t wordLength;
	std::string isogram;

	bool IsIsogram(std::string) const;
	bool IsLowerCase(std::string) const;
	void FindBullsAndCows(std::string, EvaluationResponse &);
};

#endif // !BULLCOWGAME_HH
