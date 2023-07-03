#pragma once

#include "Card.h"
#include "Player.h"

class CardFunctions
{
	std::function<std::shared_ptr<Player>()> getNextPlayerFunction;
	std::function<std::shared_ptr<Card::Card>()> buyACardFunction;
	std::function<void()> goToNextTurnFunction;

public:
	void Act(const Card::Type& CardType);
	void SetFunction_GetNextPlayer(const std::function<std::shared_ptr<Player>()>& Func);
	void SetFunction_BuyACard(const std::function<std::shared_ptr<Card::Card>()>& Func);
	void SetFunction_GoToNextTurn(const std::function<void()>& Func);

private:
	void PlusTwo();
	void BuyCards(const int Amount, std::shared_ptr<Player>& Player);
};

