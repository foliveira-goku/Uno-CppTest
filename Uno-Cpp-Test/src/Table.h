#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "Card.h"

class Table
{
private:
	std::vector<std::shared_ptr<Card::Card>> deck{};
	std::vector<std::shared_ptr<Card::Card>> discardPile{};

	const int TOTAL_NUMBER_OF_CARDS = 104;
	const int TOTAL_NUMERIC_CARDS = 10;
	const int TOTAL_PLUS_TWO_CARDS = 2;
	const int TOTAL_REVERSE_CARDS = 2;
	const int TOTAL_JUMP_CARDS = 2;
	const int NUMBER_OF_CARDS_IN_A_NEW_HAND = 3;

public:
	Table();
	void CreateColoredCards(Card::Color Color, int& Id);
	void CreateNumericCards(Card::Color Color, int& Id);
	void CreateCardAndAddToDeck(const int& Amount, int& Id, const int& Number, Card::Color Color, Card::Type Type);
	void DiscardFirstCard();
	std::shared_ptr<Card::Card> BuyCardFromDeck();
	std::shared_ptr<Card::Card>& GetCurrentDiscardCard();
	std::vector<std::shared_ptr<Card::Card>> GetNewHandOfCards();
	void DiscardCard(const std::shared_ptr<Card::Card> CardToDiscard);
	void RetreiveCardsFromDiscardToDeck();
	void ShuffleCards(std::vector<std::shared_ptr<Card::Card>>& CardsToShuffle);

private:
	void CreateDeck();
};

