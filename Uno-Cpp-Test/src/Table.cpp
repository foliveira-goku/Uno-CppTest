#include "Table.h"

Table::Table()
{
	deck.reserve(TOTAL_NUMBER_OF_CARDS);
	discardPile.reserve(TOTAL_NUMBER_OF_CARDS);
	CreateDeck();
}

void Table::CreateDeck()
{
	int currentId = 0 ;
	//CreateColoredCards(Card::Color::Blue, currentId);
	//CreateColoredCards(Card::Color::Red, currentId);
	//CreateColoredCards(Card::Color::Yellow, currentId);
	CreateColoredCards(Card::Color::Green, currentId);
	CreateCardAndAddToDeck(TOTAL_PLUS_FOUR_CARDS, currentId, -1, 
						   Card::Color::Black, Card::Type::PlusFour);

	std::cout << "Deck created with " << deck.size() << " cards.\n";
}

void Table::CreateColoredCards(Card::Color Color, int& Id)
{
	CreateNumericCards(Color, Id);
	CreateCardAndAddToDeck( TOTAL_PLUS_TWO_CARDS, Id, -1, Color, Card::Type::PlusTwo);
	CreateCardAndAddToDeck(TOTAL_REVERSE_CARDS, Id, -1, Color, Card::Type::Reverse);
	CreateCardAndAddToDeck(TOTAL_JUMP_CARDS,Id, -1, Color, Card::Type::Jump);
	CreateCardAndAddToDeck(TOTAL_JUMP_CARDS,Id, -1, Color, Card::Type::Jump);
}

void Table::CreateNumericCards(const Card::Color Color, int& Id)
{
	for (int i = 0; i < TOTAL_NUMERIC_CARDS; i++)
		CreateCardAndAddToDeck(2, Id, i, Color, Card::Type::Number);
}

void Table::CreateCardAndAddToDeck(const int Amount, int& Id, const int Number, Card::Color Color, Card::Type Type)
{
	for (int i = 0; i < Amount; i++)
	{
		deck.emplace_back(new Card::Card{ Id, Number, Color, Type });
		Id++;
	}
}

void Table::DiscardFirstCard()
{
	std::shared_ptr<Card::Card> card = BuyCardFromDeck();
	DiscardCard(card);
}

std::shared_ptr<Card::Card> Table::BuyCardFromDeck()
{
	int randomIndex = RandomHelper::GetRandomNumber(deck.size());
	std::shared_ptr<Card::Card> chosenCard = deck[randomIndex];
	deck.erase(deck.begin() + randomIndex);
	
	if (deck.size() <= 0)
	{
		std::cout << "\nThe deck is empty...\n";
		RetreiveCardsFromDiscardToDeck();
	}
	
	return chosenCard;
}

std::shared_ptr<Card::Card>& Table::GetCurrentDiscardCard()
{ return discardPile[discardPile.size() - 1]; }

std::vector<std::shared_ptr<Card::Card>> Table::GetNewHandOfCards()
{
	std::vector<std::shared_ptr<Card::Card>> handOfCards;
	handOfCards.reserve(NUMBER_OF_CARDS_IN_A_NEW_HAND);

	for (int i = 0; i < NUMBER_OF_CARDS_IN_A_NEW_HAND; i++)
		handOfCards.emplace_back(BuyCardFromDeck());

	return handOfCards;
}

void Table::DiscardCard(const std::shared_ptr<Card::Card> CardToDiscard)
{
	std::cout << "\nDiscarting card: " << CardToDiscard->GetInfo() << "\n";
	discardPile.emplace_back(CardToDiscard);
}

void Table::RetreiveCardsFromDiscardToDeck()
{
	std::cout << "Retreiving cards from discard pile to the deck...\n";
	std::shared_ptr<Card::Card> topCardFromDiscardPile = std::move(discardPile[discardPile.size()-1]);
	discardPile.erase(discardPile.begin() + (discardPile.size() - 1));

	RandomHelper::SuffleVector<std::shared_ptr<Card::Card>>(discardPile);
	deck = std::move(discardPile);

	discardPile.push_back(topCardFromDiscardPile);
}