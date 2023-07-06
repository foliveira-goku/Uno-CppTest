#include "InputReader.h"

const int InputReader::GetAmountOfPlayers()
{
	std::cout << "How many players? (" << MIN_AMOUNT_OF_PLAYERS << " - " << MAX_AMOUNT_OF_PLAYERS << ")\n";
	int playersAmount;

	return GetValidNumber(playersAmount, MIN_AMOUNT_OF_PLAYERS, MAX_AMOUNT_OF_PLAYERS);
}

const std::string InputReader::GetPlayerName(const int PlayerId)
{
	std::string name;
	std::cout << "Player " << PlayerId << "'s name:\n";
	std::cin >> name;

	return name;
}

const int InputReader::GetPlayerAction(const std::string& ActionsText, const int AmountOfActions)
{
	int actionInput = 0;
	return GetValidNumber(actionInput, 0, AmountOfActions, ActionsText + "\n");
}

const int InputReader::GetNewCardColor()
{
	std::cout << "\nChoose the new color:\n" <<
		"| [1] Red | [2] Blue | [3] Yellow | [4] Green |\n";
	int colorNumber;

	return GetValidNumber(colorNumber, 1 ,4);
}

const int InputReader::GetValidNumber(int& TheNumber, int MinValue, int MaxValue, std::string OptionalText)
{
	while (true)
	{
		std::cout << OptionalText;
		std::cin >> TheNumber;

		if (!std::cin.fail() && TheNumber >= MinValue && TheNumber <= MaxValue)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return TheNumber;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid number.\n";
	}

	return TheNumber;
}
