#include "Table.h"
#include "InputReader.h"
#include "Player.h"

const int GetActionInputsOptions(std::string& ActionsDisplay)
{
	ActionsDisplay = "[1] Discard a card  [2] Buy a card  [3] Say Uno! \n";

	return 3;
}

int main()
{
	std::srand(std::time(0));

	Table table{};
	InputReader inputReader{};
	int playersAmount = inputReader.GetAmountOfPlayers();
	std::vector<Player> players{};
	players.reserve(playersAmount);

	for (size_t i = 0; i < playersAmount; i++)
	{
		players.emplace_back(inputReader.GetPlayerName(), i+1, table.GetNewHandOfCards());
		std::cout << players[i].GetInfo() << "\n";
	}
}