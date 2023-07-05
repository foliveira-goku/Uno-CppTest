#pragma once

#include <functional>
#include "Player.h"
#include "RandomHelper.h"

struct CardIdTypePair
{
	int Id;
	Card::Type Type;
};

struct PlayerOptions
{
	int OptionsCount{};
	std::string OptionsText{};
	std::vector<CardIdTypePair> PossibleCards;
};

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
	std::shared_ptr<Card::Card> GetDiscardCardFromCurrentPlayer(const int CardId);
	void NextTurn();
	const std::shared_ptr<Player>& GetNextPlayer() const;
	const std::string GetCurrentPlayerName() const;
	const int GetPlayersCount() const;
	const PlayerOptions GetPlayerPossibleOptions(const bool CanBuyCard = true) const;
	const bool IsCurrentPlayerInUnoState();
	const int GetCurrentPlayerCardsCount();
	void SetCurrentPlayerUnoState(const bool IsInUnoState);
	void ShufflePlayersAndSetId();

private:
	bool AreCardsCompatible(std::shared_ptr<Card::Card>& DiscardCard, std::shared_ptr<Card::Card>& OtherCard) const;
	int GetNextPlayerIndex() const;
};