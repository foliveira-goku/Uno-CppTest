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
	static constexpr const char BuyACardText[] = "Buy a card";
	static constexpr const char UnoText[] = "UNO!";

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
	PlayerOptions GetPlayerPossibleOptions(PlayerSelection::Options PlayerChoice, const bool CanBuyCard, 
										   const bool CheckForPlusTwo);
	const bool NextPlayerHasPlusTwo() const;
	const bool IsPlayerInUnoState(const PlayerSelection::Options PlayerChoice) const;
	const int GetPlayerCardsCount(const PlayerSelection::Options PlayerChoice);
	void SetPlayerUnoState(const bool IsInUnoState, const PlayerSelection::Options PlayerChoice);
	void ShufflePlayersAndSetId();
	void GoToNextTurn();

private:
	void AddPossibleCardsToPlayerOptions(PlayerOptions& PlayerOptions, const std::shared_ptr<Card::Card>& CurrentDiscardCard, 
										const std::vector<std::shared_ptr<Card::Card>>& CurrentPlayerCards, const bool CheckForPlusTwo);
	bool AreCardsCompatible(const std::shared_ptr<Card::Card>& DiscardCard, const std::shared_ptr<Card::Card>& OtherCard) const;
	int GetPlayerIndex(const PlayerSelection::Options ChosenPlayer) const;
};