#pragma once

#include <functional>
#include "Player.h"
#include "RandomHelper.h"
#include "PlayerOptions.h"
#include "PlayerSelection.h"

class PlayersController
{
private:
	int currentPlayerIndex = 0;
	std::vector<std::shared_ptr<Player>> players{};
	std::function<std::shared_ptr<Card::Card>&()> function_GetCurrentDiscardCard;

	static constexpr const char PlayerOptionFormat[] = " [{}] {} |";

public:
	PlayersController() = default;
	PlayersController(const int AmountOfPlayers);
	void SetFunction_GetCurrentDiscardCard(const std::function<std::shared_ptr<Card::Card>& ()>& Function);
	void CreatePlayer(const std::string& Name, const std::vector<std::shared_ptr<Card::Card>>& Cards);
	void ReservePlayersOrder();
	void GiveCardToPlayer(const std::shared_ptr<Card::Card> Card, const PlayerSelection::Options ChosenPlayer);
	std::shared_ptr<Card::Card> GetPlayerCardById(const int CardId, const PlayerSelection::Options ChosenPlayer);
	std::string_view GetPlayerName(const PlayerSelection::Options PlayerChoice) const;
	const int GetPlayersCount() const;
	PlayerOptions GetPlayerPossibleOptions(const bool CanBuyCard = true) const;
	const bool NextPlayerHasPlusTwo() const;
	PlayerOptions GetNextPlayerPossiblePlusTwoOptions(bool _) const;
	const bool IsPlayerInUnoState(const PlayerSelection::Options PlayerChoice) const;
	const int GetPlayerCardsCount(const PlayerSelection::Options PlayerChoice);
	void SetPlayerUnoState(const bool IsInUnoState, const PlayerSelection::Options PlayerChoice);
	void ShufflePlayersAndSetId();
	void GoToNextTurn();

private:
	bool AreCardsCompatible(const std::shared_ptr<Card::Card>& DiscardCard, const std::shared_ptr<Card::Card>& OtherCard) const;
	int GetPlayerIndex(const PlayerSelection::Options ChosenPlayer) const;
};