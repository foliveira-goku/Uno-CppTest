#include "Player.h"

Player::Player(const std::string& Name, const std::vector<std::shared_ptr<Card::Card>>& InitialCards) :
	nickname{ Name }, id{ 0 }, cards{ InitialCards }, isInUnoState{ false }
{
	UpdatePlayerName();
}

void Player::SetId(const int NewId)
{
	id = NewId;
	UpdatePlayerName();
}

void Player::UpdatePlayerName()
{
	playerName.clear();
	playerName.append("Player ").append(std::to_string(id)).append("(").append(nickname).append(")");
}

std::string_view Player::GetName() const { 	return playerName; }

const std::vector<std::shared_ptr<Card::Card>>& Player::GetCards() const { return cards; }

const bool Player::IsInUnoState() const { return isInUnoState; }

const std::string Player::GetInfo() { return std::string{playerName}.append("\n").append(GetAllCardsNames()); }

void Player::SetUnoState(const bool IsInUnoState) { isInUnoState = IsInUnoState; }

void Player::ReceiveACard(const std::shared_ptr<Card::Card> NewCard)
{
	std::cout << playerName << " received the card: " << NewCard->GetInfo() << "\n";
	cards.emplace_back(NewCard);
}

std::string Player::GetAllCardsNames()
{
	std::string cardsNames{"Cards:\n"};

	for (int i = 0; i < cards.size(); i++)
		cardsNames.append(cards[i]->GetInfo()).append("\n");

	return cardsNames;
}

std::shared_ptr<Card::Card> Player::GetCardById(const int CardId)
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