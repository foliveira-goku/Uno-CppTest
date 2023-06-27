#include "Player.h"

Player::Player(const std::string& Name, const int& ID, const std::vector<std::shared_ptr<Card::Card>>& InitialCards) :
	name{Name}, id{ID}, cards{InitialCards}, isInUnoState{false}
{}

const std::string Player::GetName() const { return name; }

const std::vector<std::shared_ptr<Card::Card>>& Player::GetCards() const { return cards; }

const std::string Player::GetInfo()
{
	return "Player " + std::to_string(id) + "(" + GetName() + ") " + "\n" +
		"Cards:\n" + GetAllCardsNames();
}

const bool Player::IsInUnoState() const { return isInUnoState; }

void Player::SetUnoState(const bool& IsInUnoState) {	isInUnoState = IsInUnoState; }

std::string Player::GetAllCardsNames()
{
	std::string cardsNames{}; //TODO move this instead of copying?

	for (size_t i = 0; i < cards.size(); i++)
		cardsNames += cards[i].get()->GetInfo() + "\n";

	return cardsNames;
}
