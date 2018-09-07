#include "BullCowGame.hh"

const std::string BullCowGame::Introduction1 = "Welcome to Bulls and Cows, a fun word game.\nCan you guess which ";
const std::string BullCowGame::Introduction2 = " letter isogram I've got in mind?\n";

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
	if(currentAttempt < maxAttempts)
	{
		currentAttempt++;
		FindBullsAndCows(guess, resp);
	}

	if(resp.bulls == isogram.length())
		won = true;

	return resp;
}

// Detect the number of Bulls and Cows within the guess.
void BullCowGame::FindBullsAndCows(std::string guess, EvaluationResponse &resp)
{
	for(size_t i = 0; i < isogram.length(); i++)
	{
		for(size_t j = 0; j < guess.length(); j++)
		{
			if(isogram[i] == guess[j])
			{
				if(i == j)
					resp.bulls++;
				else
					resp.cows++;
			}
		}
	}
}

std::string BullCowGame::GetIntroduction() const
{
	std::ostringstream os;
	os << BullCowGame::Introduction1
		<< GetIsogramLength()
		<< BullCowGame::Introduction2;

	return os.str();
}

bool BullCowGame::IsIsogram(std::string guess) const
{
	bool out = true;
	for(size_t i = 1; i < guess.length(); i++)
	{
		out = guess[i] != guess[i - 1];
		if(!out)
			break;
	}
	return out;
}

bool BullCowGame::IsLowerCase(std::string guess) const
{
	//TODO: Implement this validation
	return true;
}

void BullCowGame::Reset()
{
	currentAttempt = 0;
	won = false;
	isogram = "filer";
}

GuessStatus BullCowGame::ValidateGuess(std::string guess) const
{
	if(!IsLowerCase(guess))
		return GuessStatus::NotLowerCase;

	if(guess.length() != isogram.length())
		return GuessStatus::NotLongEnough;

	if(!IsIsogram(guess))
		return GuessStatus::NotIsogram;

	return GuessStatus::Ok;
}
