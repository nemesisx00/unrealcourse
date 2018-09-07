#include "main.hh"

int main()
{
	constexpr int MaxAttempts = 6;
	constexpr int WordLength = 5;
	BullCowGame game(MaxAttempts, WordLength);

	do
	{
		std::cout << game.GetIntroduction();
		playGame(game);
	} while(shouldPlayAgain());

	return 0;
}
