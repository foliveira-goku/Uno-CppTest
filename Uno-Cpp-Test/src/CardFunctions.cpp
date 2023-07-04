#include "CardFunctions.h"

void CardFunctions::Act(const Card::Type& CardType)
{
	switch (CardType)
	{
	case Card::Type::Number:
		return;
	case Card::Type::PlusTwo:
		PlusTwo();
		break;
	case Card::Type::Reverse:
		Reverse();
		break;
	case Card::Type::Jump:
		Jump();
		break;
	default:
		break;
	}
}

void CardFunctions::SetFunction_GetNextPlayer(const std::function<std::shared_ptr<Player>()>& Func)
{
	getNextPlayerFunction = Func;
}

void CardFunctions::SetFunction_BuyACard(const std::function<std::shared_ptr<Card::Card>()>& Func)
{
	buyACardFunction = Func;
}

void CardFunctions::SetFunction_GoToNextTurn(const std::function<void()>& Func)
{
	goToNextTurnFunction = Func;
}

void CardFunctions::SetFunction_ReversePlayersOrder(const std::function<void()>& Func)
{
	reversePlayersOrderFunction = Func;
}

void CardFunctions::PlusTwo()
{
	std::shared_ptr<Player> nextPlayer = getNextPlayerFunction();
	std::cout << "\nA +2 card has been applied to " << nextPlayer->GetName() << "\n";

	BuyCards(2, nextPlayer);

	std::cout << "\n" << nextPlayer->GetName() << " has lost their turn...\n";
	goToNextTurnFunction();
}

void CardFunctions::Reverse()
{
	std::cout << "\nThe player order was reversed!\n";
	reversePlayersOrderFunction();
}

void CardFunctions::Jump()
{
	std::cout << "\n" << getNextPlayerFunction()->GetName() << " was jumped!\n";

	goToNextTurnFunction();
}

void CardFunctions::BuyCards(const int Amount, std::shared_ptr<Player>& Player)
{
	for (int i = 0; i < Amount; i++)
	{
		std::shared_ptr<Card::Card> newCard = buyACardFunction();
		Player->ReceiveACard(newCard);
	}

	std::cout << "\n";
}
