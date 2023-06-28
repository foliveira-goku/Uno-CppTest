#pragma once
#include "Player.h"

class PlayersController
{
private:
	std::vector<std::shared_ptr<Player>> players{};
	int currentPlayerIndex = 0;

public:
	PlayersController() = default;
	PlayersController(const int& AmountOfPlayers);
	void CreatePlayer(const std::string& Name, const int& ID, const std::vector<std::shared_ptr<Card::Card>>& Cards);
	void ReservePlayersOrder();
	const int GetPlayersCount() const;
	const int GetPlayerPossibleOptions(std::string& ActionsText) const;
};