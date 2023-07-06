#pragma once

#include <functional>
#include "Player.h"
#include "RandomHelper.h"
#include "PlayerOptions.h"

class PlayersController
{
private:
	std::vector<std::shared_ptr<Player>> players{};
	int currentPlayerIndex = 0;
	std::function<std::shared_ptr<Card::Card>&()> getCurrentDiscardCardFunction;

public:
	PlayersController() = default;
	PlayersController(const int AmountOfPlayers);
	void SetFunction_GetCurrentDiscardCard(const std::function<std::shared_ptr<Card::Card>& ()>& Function);
	void CreatePlayer(const std::string& Name, const std::vector<std::shared_ptr<Card::Card>>& Cards);
	void ReservePlayersOrder();
	void GiveCardToCurrentPlayer(const std::shared_ptr<Card::Card> card);
	void GiveCardToNextPlayer(const std::shared_ptr<Card::Card> card);
	std::shared_ptr<Card::Card> GetPlayerCardById(const int CardId);
	std::shared_ptr<Card::Card> GetNextPlayerCardById(const int CardId);
	void NextTurn();
	const std::string GetCurrentPlayerName() const;
	const std::string GetNextPlayerName() const;
	const int GetPlayersCount() const;
	PlayerOptions GetPlayerPossibleOptions(const bool CanBuyCard = true) const;
	const bool NextPlayerHasPlusTwo() const;
	PlayerOptions GetNextPlayerPossiblePlusTwoOptions(bool _) const;
	const bool IsCurrentPlayerInUnoState();
	const int GetCurrentPlayerCardsCount();
	void SetCurrentPlayerUnoState(const bool IsInUnoState);
	void ShufflePlayersAndSetId();

private:
	bool AreCardsCompatible(std::shared_ptr<Card::Card>& DiscardCard, std::shared_ptr<Card::Card>& OtherCard) const;
	int GetNextPlayerIndex(const int AmountForward = 1) const;
};