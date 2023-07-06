#pragma once

#include "Card.h"
#include "Player.h"

class CardFunctions
{
	std::function<const std::string()> function_GetNextPlayerName{};
	std::function<std::shared_ptr<Card::Card>()> function_BuyACard{};
	std::function<void()> function_GoToNextTurn{};
	std::function<void()> function_ReversePlayersOrder{};
	std::function<const bool()> function_NextPlayerHasPlusTwo{};
	std::function<void()> function_ProcessNextPlayerPlusTwoTurn{};
	std::function<void(std::shared_ptr<Card::Card>)> function_GiveCardToPlayer{};

	int plusTwoAmount{};

public:
	void Act(const Card::Type& CardType);
	void SetFunction_GetNextPlayerName(const std::function<const std::string()>& Func);
	void SetFunction_BuyACard(const std::function<std::shared_ptr<Card::Card>()>& Func);
	void SetFunction_GoToNextTurn(const std::function<void()>& Func);
	void SetFunction_ReversePlayersOrder(const std::function<void()>& Func);
	void SetFunction_NextPlayerHasPlusTwo(const std::function<const bool()>& Func);
	void SetFunction_ProcessNextPlayerPlusTwoTurn(const std::function<void()>& Func);
	void SetFunction_GiveCardToPlayer(const std::function<void(std::shared_ptr<Card::Card>)>& Func);

private:
	void PlusTwo();
	void Reverse();
	void Jump();
	std::vector<std::shared_ptr<Card::Card>> BuyCards(const int Amount);
};

