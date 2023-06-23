#include "Card.h"

namespace Card
{
	Card::Card(const int Number, const Color Color, const Type CardType) :
		number{ Number }, color{ Color }, cardType{ CardType }
	{
#if _DEBUG
		if(number >= 0)
			std::cout << "Card created: " << cardType << " " << number << " " << color << "\n";
		else
			std::cout << "Card created: " << cardType << " " << color << "\n";
#endif
	}

	const Color Card::GetColor() const { return color; }

	const int Card::GetNumber() const { return number; }

	void Card::TryProcessAction() {	}

	std::ostream& operator<<(std::ostream& os, const Type& value)
	{
		switch (value)
		{
		case Type::Number:
			os << "Number";
			break;
		case Type::PlusTwo:
			os << "+2";
			break;
		case Type::Reverse:
			os << "Reverse";
			break;
		case Type::Jump:
			os << "Jump";
			break;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Color& value)
	{
		switch (value)
		{
		case Color::Blue:
			os << "Blue";
			break;
		case Color::Red:
			os << "Red";
			break;
		case Color::Yellow:
			os << "Yellow";
			break;
		case Color::Green:
			os << "Green";
			break;
		}
		return os;
	}
}