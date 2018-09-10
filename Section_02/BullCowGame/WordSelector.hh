#ifndef WORDSELECTOR_HH
#define WORDSELECTOR_HH

#include <array>
#include <list>
#include <map>
#include <random>

enum class WordLength
{
	Four = 4,
	Five,
	Six
};

class WordSelector
{
public:
	WordSelector();

	std::string SelectWord(WordLength);

private:
	std::map<WordLength, std::map<size_t, std::string>> words = {
		{ WordLength::Four, { {0,"arms"}, {1,"bowl"}, {2,"cant"}, {3,"dues"}, {4,"each"}, {5,"fire"} } },
		{ WordLength::Five, { {0,"games"}, {1,"hotel"}, {2,"ingot"}, {3,"judge"}, {4,"knead"}, {5,"lying"} } },
		{ WordLength::Six, { {0,"melons"}, {1,"normal"}, {2,"orchid"}, {3,"pastor"}, {4,"quince"}, {5,"royale"} } }
	};
};

#endif //!WORDSELECTOR_HH
