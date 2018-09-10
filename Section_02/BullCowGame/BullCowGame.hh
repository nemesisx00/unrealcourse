#ifndef BULLCOWGAME_HH
#define BULLCOWGAME_HH

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "EvaluationResponse.hh"
#include "WordSelector.hh"

enum class GuessStatus
{
	Invalid,
	Ok,
	LengthMismatch,
	NotAllLetters,
	NotIsogram,
	NotLowerCase
};

class BullCowGame
{
public:
	BullCowGame();

	size_t GetCurrentAttempt() const;
	size_t GetIsogramLength() const;
	size_t GetMaxAttempts() const;

	void SetIsogramLength(WordLength);

	bool IsGameWon() const;
	GuessStatus ValidateGuess(std::string) const;

	void Reset();
	EvaluationResponse EvaluateGuess(std::string);

private:
	bool won;
	size_t currentAttempt;
	size_t maxAttempts;
	std::string isogram;
	WordLength wordLength;
	WordSelector selector;

	bool IsAllLetters(std::string) const;
	bool IsIsogram(std::string) const;
	bool IsLowerCase(std::string) const;
	void FindBullsAndCows(std::string, EvaluationResponse &);
};

#endif //!BULLCOWGAME_HH
