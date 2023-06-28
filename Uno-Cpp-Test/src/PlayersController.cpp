#include "PlayersController.h"

PlayersController::PlayersController(const int& AmountOfPlayers)
{ players.reserve(AmountOfPlayers); }

void PlayersController::CreatePlayer(const std::string& Name, const int& ID, 
	const std::vector<std::shared_ptr<Card::Card>>& Cards)
{ players.emplace_back(new Player{ Name, ID, Cards }); }

void PlayersController::ReservePlayersOrder() { std::reverse(players.begin(), players.end()); }

const int PlayersController::GetPlayersCount() const {	return players.capacity(); }

const int PlayersController::GetPlayerPossibleOptions(std::string& ActionsText) const
{
	auto currentPlayer = players[currentPlayerIndex];
	auto currentPlayerCards = currentPlayer->GetCards();
	int cardsAmount = currentPlayerCards.size();
	int optionsCount = cardsAmount;

	for (int i = 0; i < cardsAmount; i++)
		ActionsText += "[" + std::to_string(i + 1) + "] " + currentPlayerCards[i]->GetInfo() + " ";

	optionsCount++;
	ActionsText += "[" + std::to_string(optionsCount) + "] Buy a card.";

	if (currentPlayer->IsInUnoState())
	{
		optionsCount++;
		ActionsText += "[" + std::to_string(optionsCount) + "] UNO!";
	}

	return optionsCount;
}
