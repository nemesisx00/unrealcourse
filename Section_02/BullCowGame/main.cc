#include "main.hh"

int main()
{
	BullCowGame game;
	bool playingAgain = false;

	do
	{
		printIntroduction(game, playingAgain);
		game.SetIsogramLength(getWordLength());
		playGame(game);
		playingAgain = shouldPlayAgain();
	} while(playingAgain);

	return 0;
}
