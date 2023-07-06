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
	case Card::Type::PlusFour:
		PlusFour();
		break;
	default:
		break;
	}
}

void CardFunctions::SetFunction_GetNextPlayerName(const std::function<const std::string()>& Func)
{
	function_GetNextPlayerName = Func;
}

void CardFunctions::SetFunction_BuyACard(const std::function<std::shared_ptr<Card::Card>()>& Func)
{
	function_BuyACard = Func;
}

void CardFunctions::SetFunction_GoToNextTurn(const std::function<void()>& Func)
{
	function_GoToNextTurn = Func;
}

void CardFunctions::SetFunction_ReversePlayersOrder(const std::function<void()>& Func)
{
	function_ReversePlayersOrder = Func;
}

void CardFunctions::SetFunction_NextPlayerHasPlusTwo(const std::function<const bool()>& Func)
{
	function_NextPlayerHasPlusTwo = Func;
}

void CardFunctions::SetFunction_ProcessNextPlayerPlusTwoTurn(const std::function<void()>& Func)
{
	function_ProcessNextPlayerPlusTwoTurn = Func;
}

void CardFunctions::SetFunction_GiveCardToPlayer(const std::function<void(std::shared_ptr<Card::Card>)>& Func)
{
	function_GiveCardToPlayer = Func;
}

void CardFunctions::SetFunction_GetPlayerColorInput(const std::function<Card::Color()>& Func)
{
	function_GetPlayerColorInput = Func;
}

void CardFunctions::SetFunction_ChangeCurrentCardColor(const std::function<void(Card::Color)>& Func)
{
	function_ChangeCurrentCardColor = Func;
}

void CardFunctions::PlusTwo()
{
	plusTwoAmount = 1;

	while (true)
	{
		std::cout << "\nA +2 card has been applied to " << function_GetNextPlayerName() << ".\n"
			<< "Total cards to buy: " << plusTwoAmount * 2 << "\n";

		if (function_NextPlayerHasPlusTwo())
		{
			function_ProcessNextPlayerPlusTwoTurn();
			function_GoToNextTurn();
			plusTwoAmount++;
		}
		else
		{
			auto playerName = function_GetNextPlayerName();

			std::cout << "\n" << playerName << " doesn't have a +2 card.\n";

			auto cards = BuyCards(plusTwoAmount * 2);
			
			for (int i = 0; i < cards.size(); i++)
				function_GiveCardToPlayer(cards[i]);
			
			std::cout << "\n" << playerName << " has lost their turn...\n";
			function_GoToNextTurn();
			return;
		}
	}
}

void CardFunctions::Reverse()
{
	std::cout << "\nThe player order was reversed!\n";
	function_ReversePlayersOrder();
}

void CardFunctions::Jump()
{
	std::cout << "\n" << function_GetNextPlayerName() << " was jumped!\n";

	function_GoToNextTurn();
}

void CardFunctions::PlusFour()
{
	auto color = function_GetPlayerColorInput();
	function_ChangeCurrentCardColor(color);

	auto playerName = function_GetNextPlayerName();

	std::cout << "\nA +4 card was applied to " << playerName << "!\n";

	auto cards = BuyCards(4);

	for (int i = 0; i < cards.size(); i++)
		function_GiveCardToPlayer(cards[i]);

	std::cout << "\n" << playerName << " has lost their turn...\n";
	function_GoToNextTurn();
}

std::vector<std::shared_ptr<Card::Card>> CardFunctions::BuyCards(const int Amount)
{
	std::vector<std::shared_ptr<Card::Card>> cardsBought {};
	cardsBought.reserve(Amount);

	for (int i = 0; i < Amount; i++)
	{
		std::shared_ptr<Card::Card> newCard = function_BuyACard();
		cardsBought.emplace_back(newCard);
	}

	std::cout << "\n";

	return cardsBought;
}
