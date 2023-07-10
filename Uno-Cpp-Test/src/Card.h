#pragma once
#include <iostream>
#include <functional>
#include <string>

namespace Card
{
	enum class Type	{ Number, PlusTwo, Reverse, Jump , PlusFour }; 

	std::ostream& operator<<(std::ostream& os, const Type& value);
	
	enum class Color { Black, Red, Blue, Yellow, Green };

	std::ostream& operator<<(std::ostream& os, const Color& value);

	class Card
	{
	private:
		const int number{};
		const int id{};
		Color color{};
		Type cardType{};
		std::string cardInfo{};

	public:
		Card() = default;
		Card(const int Id, const int Number, const Color Color, const Type CardType);
		const int GetNumber() const;
		const int GetId() const;
		const Color GetColor() const;
		const Type GetType() const;
		std::string_view GetInfo() const;
		void ChangeColor(const Color NewColor);
	private:
		void SetCardInfo();
	};
}