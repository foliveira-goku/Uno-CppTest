#include "Table.h"

int main()
{
	std::srand(std::time(0));

	Table table;
	table.CreateDeck();

	auto cards = table.GetNewHandOfCards();

	for (size_t i = 0; i < cards.size(); i++)
	{
		std::cout << cards[i]->GetColor() << " " << cards[i]->GetType() << " " << cards[i]->GetNumber() <<"\n";
	}

	//auto card = table.BuyCardFromDeck();
	//std::cout << card->GetColor() << " " << card->GetType() << " " << card->GetNumber();
}