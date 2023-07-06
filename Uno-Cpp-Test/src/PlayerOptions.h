#pragma once

#include <iostream>
#include <vector>
#include "Card.h"

struct CardIdTypePair
{
	int Id;
	Card::Type Type;
};

struct PlayerOptions
{
	int OptionsCount{};
	std::string OptionsText{};
	std::vector<CardIdTypePair> PossibleCards;
};