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
		}

		return std::string{};
	}

	std::string Type_ToString(const Type& value)
	{
		switch (value)
		{
		case Type::Number:
			return "Number";
			break;
		case Type::PlusTwo:
			return "+2";
			break;
		case Type::Reverse:
			return "Reverse";
			break;
		case Type::Jump:
			return "Jump";
			break;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Type& value) { return os << Type_ToString(value); }

	std::ostream& operator<<(std::ostream& os, const Color& value) { return os << Color_ToString(value); }
}