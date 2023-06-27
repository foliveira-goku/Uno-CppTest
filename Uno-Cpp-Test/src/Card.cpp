#include "Card.h"
#include "CardHelper.h"

namespace Card
{
	Card::Card(const int Number, const Color Color, const Type CardType) :
		number{ Number }, color{ Color }, cardType{ CardType }
	{
//#if _DEBUG
//		if(number >= 0)
//			std::cout << "Card created: " << cardType << " " << number << " " << color << "\n";
//		else
//			std::cout << "Card created: " << cardType << " " << color << "\n";
//#endif
	}

	const Color Card::GetColor() const { return color; }

	const int Card::GetNumber() const { return number; }

	const Type Card::GetType() const	{ return cardType;	}

	void Card::TryProcessAction() {	}

	std::string Card::GetInfo() const
	{
		if (GetNumber() < 0)
			return Type_ToString(cardType) + " " + Color_ToString(color);

		return Type_ToString(cardType) + " " + std::to_string(number) + " " + Color_ToString(color) ;
	}

}