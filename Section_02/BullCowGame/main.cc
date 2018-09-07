#include "main.hh"

int main()
{
	constexpr size_t MaxAttempts = 6;
	BullCowGame game(MaxAttempts);

	do
	{
		std::cout << game.GetIntroduction();
		playGame(game);
	} while(shouldPlayAgain());

	return 0;
}
