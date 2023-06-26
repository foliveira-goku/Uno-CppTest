#pragma once
#include <iostream>
#include <functional>
#include <string>

namespace Card
{
	enum class Type	{ Number, PlusTwo, Reverse, Jump }; 

	std::ostream& operator<<(std::ostream& os, const Type& value);
	
	enum class Color { Black, Red, Blue, Yellow, Green };

	std::ostream& operator<<(std::ostream& os, const Color& value);

	class Card
	{
	private:
		const int number{};
		Color color{};
		Type cardType{};
		std::function<void()> action{};

	public:
		Card() = default;
		Card(const int Number, const Color Color, const Type CardType);
		const Color GetColor() const;
		const int GetNumber() const;
		const Type GetType() const;
		void TryProcessAction();
	};
}