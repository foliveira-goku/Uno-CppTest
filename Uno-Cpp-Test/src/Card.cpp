#include "Card.h"
#include "CardHelper.h"

namespace Card
{
	Card::Card(const int Id, const int Number, const Color Color, const Type CardType) :
		id{Id}, number{ Number }, color{ Color }, cardType{ CardType }
	{
		SetCardInfo();
	}

	const Color Card::GetColor() const { return color; }

	const int Card::GetNumber() const { return number; }

	const int Card::GetId() const { return id; }

	const Type Card::GetType() const { return cardType;	}

	std::string_view Card::GetInfo() const { return cardInfo; }

	void Card::ChangeColor(const Color NewColor) 
	{ 
		color = NewColor;
		SetCardInfo();
	}

	void Card::SetCardInfo()
	{
		if (number < 0)
		{
			cardInfo = Type_ToString(cardType).append(" ").append(Color_ToString(color));
			return;
		}

		cardInfo = Type_ToString(cardType).append(" ").append(std::to_string(number))
			       .append(" ").append(Color_ToString(color));	
	}
}