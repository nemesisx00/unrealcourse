#include "WordSelector.hh"

WordSelector::WordSelector() { }

std::string WordSelector::SelectWord(WordLength wordLength)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dis(0, 6);

	size_t i = dis(gen);
	return words[wordLength][i];
}
