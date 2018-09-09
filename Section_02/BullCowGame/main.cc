#include "main.hh"

int main()
{
	constexpr size_t MaxAttempts = 6;
	BullCowGame game(MaxAttempts);
	bool playingAgain = false;

	do
	{
		printIntroduction(game, playingAgain);
		playGame(game);
		playingAgain = shouldPlayAgain();
	} while(playingAgain);

	return 0;
}
