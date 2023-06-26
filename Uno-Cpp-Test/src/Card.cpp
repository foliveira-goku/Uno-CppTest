#include "Card.h"

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
			std::cout << "\033[" << 34 << "m";
			os << "Blue";
			break;
		case Color::Red:
			std::cout << "\033[" << 31 << "m";
			os << "Red";
			break;
		case Color::Yellow:
			std::cout << "\033[" << 33 << "m";
			os << "Yellow";
			break;
		case Color::Green:
			std::cout << "\033[" << 32 << "m";
			os << "Green";
			break;
		}

		std::cout << "\033[" << 0 << "m";

		return os;
	}
}