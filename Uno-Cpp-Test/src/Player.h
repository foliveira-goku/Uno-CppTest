#pragma once

#include <iostream>
#include <vector>
#include "Card.h"

class Player
{
private:
	std::string name{};
	int id{};
	std::vector<std::shared_ptr<Card::Card>> cards{};
	bool isInUnoState{};

public:
	Player() = default;
	Player(const std::string& Name, const int& ID, 
		const std::vector<std::shared_ptr<Card::Card>>& InitialCards);
	const std::string GetName() const;
	const std::vector<std::shared_ptr<Card::Card>>& GetCards() const; // do we need this?
	const std::string GetInfo();
	const bool IsInUnoState() const;
	void SetUnoState(const bool& IsInUnoState);
	std::string GetAllCardsNames();
	std::shared_ptr<Card::Card> DiscardCard(const int& cardIndex);
};

