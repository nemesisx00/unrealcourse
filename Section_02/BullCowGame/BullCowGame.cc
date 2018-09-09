#include "BullCowGame.hh"

BullCowGame::BullCowGame(size_t maxAttempts)
{
	this->maxAttempts = maxAttempts;
	
	Reset();
}

size_t BullCowGame::GetCurrentAttempt() const { return currentAttempt; }
size_t BullCowGame::GetIsogramLength() const { return isogram.length(); }
size_t BullCowGame::GetMaxAttempts() const { return maxAttempts; }
bool BullCowGame::IsGameWon() const { return won; }

EvaluationResponse BullCowGame::EvaluateGuess(std::string guess)
{
	EvaluationResponse resp;
	if(currentAttempt <= maxAttempts)
	{
		currentAttempt++;
		FindBullsAndCows(guess, resp);
	}

	won = resp.bulls == isogram.length();
	return resp;
}

// Detect the number of Bulls and Cows within the guess.
void BullCowGame::FindBullsAndCows(std::string guess, EvaluationResponse &resp)
{
	for(auto letter1 : isogram)
	{
		for(auto letter2 : guess)
		{
			if(letter1 == letter2)
			{
				if(isogram.find(letter1) == guess.find(letter2))
					resp.bulls++;
				else
					resp.cows++;
			}
		}
	}
}

bool BullCowGame::IsAllLetters(std::string guess) const
{
	for(auto letter : guess)
	{
		if(!isalpha(letter))
			return false;
	}
	return true;
}

bool BullCowGame::IsIsogram(std::string guess) const
{
	std::map<char, bool> tally;
	for(auto letter : guess)
	{
		letter = tolower(letter);
		if(tally[letter])
			return false;
		tally[letter] = true;
	}
	return true;
}

bool BullCowGame::IsLowerCase(std::string guess) const
{
	for(auto letter : guess)
	{
		if(!islower(letter))
			return false;
	}
	return true;
}

void BullCowGame::Reset()
{
	currentAttempt = 1;
	won = false;
	isogram = "filer";
}

GuessStatus BullCowGame::ValidateGuess(std::string guess) const
{
	if(guess.length() != isogram.length())
		return GuessStatus::LengthMismatch;

	if(!IsAllLetters(guess))
		return GuessStatus::NotAllLetters;

	if(!IsLowerCase(guess))
		return GuessStatus::NotLowerCase;

	if(!IsIsogram(guess))
		return GuessStatus::NotIsogram;

	return GuessStatus::Ok;
}
