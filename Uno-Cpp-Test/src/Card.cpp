#include "Card.h"
#include "CardHelper.h"

namespace Card
{
	Card::Card(const int Id, const int Number, const Color Color, const Type CardType) :
		id{Id}, number{ Number }, color{ Color }, cardType{ CardType }
	{}

	const Color Card::GetColor() const { return color; }

	const int Card::GetNumber() const { return number; }

	const int Card::GetId() const { return id; }

	const Type Card::GetType() const	{ return cardType;	}

	std::string Card::GetInfo() const
	{
		if (GetNumber() < 0)
			return Type_ToString(cardType) + " " + Color_ToString(color);

		return Type_ToString(cardType) + " " + std::to_string(number) + " " + Color_ToString(color) ;
	}

	void Card::ChangeColor(const Color NewColor) { color = NewColor; }
}