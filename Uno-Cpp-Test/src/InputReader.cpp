#include "InputReader.h"

const int InputReader::GetAmountOfPlayers()
{
	int playersAmount;
	std::cout << "How many players? (" << MIN_AMOUNT_OF_PLAYERS << " - " << MAX_AMOUNT_OF_PLAYERS << ")\n";

	while (true)
	{
		std::cin >> playersAmount;

		if (!std::cin.fail() && playersAmount >= MIN_AMOUNT_OF_PLAYERS && playersAmount <= MAX_AMOUNT_OF_PLAYERS)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return playersAmount;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid number.\n";
	}

	return playersAmount;
}

const std::string InputReader::GetPlayerName(const int& PlayerId)
{
	std::string name;
	std::cout << "Player " << PlayerId << "'s name:\n";
	std::cin >> name;

	return name;
}

const int InputReader::GetPlayerAction(const std::string& ActionsText, const int& AmountOfActions)
{
	int actionInput = 0;

	while (true)
	{
		std::cout << ActionsText << "\n";
		std::cin >> actionInput;

		if (!std::cin.fail() && actionInput > 0 && actionInput <= AmountOfActions)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return actionInput;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid number.\n";
	}

	return actionInput;
}