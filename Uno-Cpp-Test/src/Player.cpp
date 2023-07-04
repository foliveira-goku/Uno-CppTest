#include "Player.h"

Player::Player(const std::string& Name, const int& ID, const std::vector<std::shared_ptr<Card::Card>>& InitialCards) :
	name{ Name }, id{ ID }, cards{ InitialCards }, isInUnoState{ false }
{
	std::cout << GetInfo() << "\n";
}

const std::string Player::GetName() const { return "Player " + std::to_string(id) + "(" + name + ")"; }

const std::vector<std::shared_ptr<Card::Card>>& Player::GetCards() const { return cards; }

const std::string Player::GetInfo() { return "\n" + GetName() + "\n" + "Cards:\n" + GetAllCardsNames(); }

const bool Player::IsInUnoState() const { return isInUnoState; }

void Player::SetUnoState(const bool& IsInUnoState) { isInUnoState = IsInUnoState; }

void Player::ReceiveACard(const std::shared_ptr<Card::Card> newCard)
{
	std::cout << GetName() << "::card received : " << newCard->GetInfo() << "\n";
	cards.push_back(newCard);
}

std::string Player::GetAllCardsNames()
{
	std::string cardsNames{}; //TODO move this instead of copying?

	for (int i = 0; i < cards.size(); i++)
		cardsNames += cards[i].get()->GetInfo() + "\n";

	return cardsNames;
}

std::shared_ptr<Card::Card> Player::GetDiscardCard(const int& CardId)
{
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards[i]->GetId() != CardId)
			continue;

		std::shared_ptr<Card::Card> card = cards[i];
		cards.erase(cards.begin() + i);
		return card;
	}

	std::cout << "Card not found!\n";
	return nullptr;
}