#include "BullCowGame.hh"

const std::string BullCowGame::Introduction1 = "Welcome to Bulls and Cows, a fun word game.\nCan you guess which ";
const std::string BullCowGame::Introduction2 = " isogram I've got in mind?\n";

BullCowGame::BullCowGame(int maxAttempts, int wordLength)
{
	maxAttempts = maxAttempts;
	wordLength = wordLength;
	
	Reset();
}

int BullCowGame::GetCurrentAttempt() const { return currentAttempt; }
int BullCowGame::GetMaxAttempts() const { return maxAttempts; }
bool BullCowGame::IsGameWon() const { return won; }

std::string BullCowGame::GetIntroduction() const
{
	std::ostringstream os;
	os << BullCowGame::Introduction1
		<< wordLength
		<< BullCowGame::Introduction2;

	return os.str();
}

bool BullCowGame::IsIsogram(std::string word)
{
	return true;
}

void BullCowGame::Reset()
{
	currentAttempt = 0;
	won = false;
	isogram = "";
}

bool BullCowGame::ValidateGuess(std::string guess)
{
	if(currentAttempt < maxAttempts)
	{
		currentAttempt++;
		if(IsIsogram(guess))
		{
			return true;
		}
	}

	return false;
}
