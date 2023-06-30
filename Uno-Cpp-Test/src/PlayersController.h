#pragma once

#include <functional>
#include "Player.h"

struct PlayerOptions
{
	int OptionsCount{};
	std::string OptionsText{};
	std::vector<std::shared_ptr<Card::Card>> PossibleCards;
};

class PlayersController
{
private:
	std::vector<std::shared_ptr<Player>> players{};
	int currentPlayerIndex = 0;
	std::function<std::shared_ptr<Card::Card>&()> getCurrentDiscardCardFunction;

public:
	PlayersController() = default;
	PlayersController(const int& AmountOfPlayers);
	void SetFunction_GetCurrentDiscardCard(const std::function<std::shared_ptr<Card::Card>& ()>& Function);
	void CreatePlayer(const std::string& Name, const int& ID, const std::vector<std::shared_ptr<Card::Card>>& Cards);
	void ReservePlayersOrder();
	void NextTurn();
	const std::string GetCurrentPlayerName() const;
	const int GetPlayersCount() const;
	const PlayerOptions GetPlayerPossibleOptions() const;

private:
	bool AreCardsCompatible(std::shared_ptr<Card::Card>& DiscardCard, std::shared_ptr<Card::Card>& OtherCard) const;
};