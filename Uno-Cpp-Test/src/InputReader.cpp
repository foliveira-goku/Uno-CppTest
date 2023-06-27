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

const std::string InputReader::GetPlayerName()
{
	std::string name;
	std::cout << "Please tell me your name.\n";
	std::cin >> name;

	return name;
}

const int InputReader::GetPlayerAction(const std::function<const int(std::string&)>& GetActionOptions)
{
	std::string actionsText = "";
	int amountOfActions = GetActionOptions(actionsText);
	int actionInput = 0;

	while (true)
	{
		std::cout << actionsText << "\n";
		std::cin >> actionInput;

		if (!std::cin.fail() && actionInput > 0 && actionInput <= amountOfActions)
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