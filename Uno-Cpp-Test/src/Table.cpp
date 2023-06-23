#include "Table.h"

Table::Table()
{
	deck.reserve(TOTAL_NUMBER_OF_CARDS);
	discardPile.reserve(TOTAL_NUMBER_OF_CARDS);
}

void Table::CreateDeck()
{
	CreateColoredCards(Card::Color::Blue);
	CreateColoredCards(Card::Color::Red);
	CreateColoredCards(Card::Color::Yellow);
	CreateColoredCards(Card::Color::Green);

	std::cout << "Deck created with " << deck.size() << " cards.\n";
}

void Table::CreateColoredCards(Card::Color Color)
{
	CreateNumericCards(Color);
	CreateCardAndAddToDeck(TOTAL_PLUS_TWO_CARDS, -1, Color, Card::Type::PlusTwo);
	CreateCardAndAddToDeck(TOTAL_REVERSE_CARDS, -1, Color, Card::Type::Reverse);
	CreateCardAndAddToDeck(TOTAL_JUMP_CARDS, -1, Color, Card::Type::Jump);
}

void Table::CreateNumericCards(const Card::Color Color)
{
	for (size_t i = 0; i < TOTAL_NUMERIC_CARDS; i++)
		CreateCardAndAddToDeck(2, i, Color, Card::Type::Number);
}

void Table::CreateCardAndAddToDeck(const int& Amount, const int& Number, Card::Color Color, Card::Type Type)
{
	for (size_t i = 0; i < Amount; i++)
		deck.emplace_back(new Card::Card{ Number, Color, Type });
}

Card::Card* Table::BuyCardFromDeck()
{
	// remove from deck
	return deck[0].get();
}

void Table::DiscardCard(const Card::Card& CardToDiscard) const
{
	// add to discardPile vector
}