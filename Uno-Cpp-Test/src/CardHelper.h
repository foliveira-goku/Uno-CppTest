#pragma once

namespace Card
{
	std::string Color_ToString(const Color& value)
	{
		switch (value)
		{
		case Color::Blue:
			return "\033[34mBlue\033[0m";
		case Color::Red:
			return "\033[31mRed\33[0m";
		case Color::Yellow:
			return "\033[33mYellow\33[0m";
		case Color::Green:
			return "\033[32mGreen\33[0m";
		case Color::Black:
			return "Black";
		}

		return std::string{};
	}

	std::string Type_ToString(const Type& value)
	{
		switch (value)
		{
		case Type::Number:
			return "Number";
		case Type::PlusTwo:
			return "+2";
		case Type::Reverse:
			return "Reverse";
		case Type::Jump:
			return "Jump";
		case Type::PlusFour:
			return "+4";
		}
	}

	std::ostream& operator<<(std::ostream& os, const Type& value) { return os << Type_ToString(value); }

	std::ostream& operator<<(std::ostream& os, const Color& value) { return os << Color_ToString(value); }
}