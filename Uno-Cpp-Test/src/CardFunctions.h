#pragma once

#include "Card.h"
#include "Player.h"
#include "PlayerSelection.h"

class CardFunctions
{
	std::function<void()> function_GoToNextTurn{};
	std::function<void()> function_ReversePlayersOrder{};
	std::function<Card::Color()> function_GetPlayerColorInput{};
	std::function<const bool()> function_NextPlayerHasPlusTwo{};
	std::function<void()> function_ProcessNextPlayerPlusTwoTurn{};
	std::function<std::shared_ptr<Card::Card>()> function_BuyACard{};
	std::function<void(Card::Color)> function_ChangeCurrentCardColor{};
	std::function<const std::string_view(PlayerSelection::Options)> function_GetPlayerName{};
	std::function<void(std::shared_ptr<Card::Card>, PlayerSelection::Options)> function_GiveCardToPlayer{};

	int plusTwoAmount{};

public:
	void Act(const Card::Type& CardType);
	void SetFunction_GoToNextTurn(const std::function<void()>& Func);
	void SetFunction_ReversePlayersOrder(const std::function<void()>& Func);
	void SetFunction_GetPlayerColorInput(const std::function<Card::Color()>& Func);
	void SetFunction_NextPlayerHasPlusTwo(const std::function<const bool()>& Func);
	void SetFunction_ProcessNextPlayerPlusTwoTurn(const std::function<void()>& Func);
	void SetFunction_BuyACard(const std::function<std::shared_ptr<Card::Card>()>& Func);
	void SetFunction_ChangeCurrentCardColor(const std::function<void(Card::Color)>& Func);
	void SetFunction_GetPlayerName(const std::function<std::string_view(PlayerSelection::Options)>& Func);
	void SetFunction_GiveCardToPlayer(const std::function<void(std::shared_ptr<Card::Card>,PlayerSelection::Options)>& Func);

private:
	void PlusTwo();
	void Reverse();
	void Jump();
	void PlusFour();
	std::vector<std::shared_ptr<Card::Card>> BuyCards(const int Amount);
};

