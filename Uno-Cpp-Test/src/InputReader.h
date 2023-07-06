#pragma once

#include <iostream>
#include <functional>

class InputReader
{
private:
	const int MIN_AMOUNT_OF_PLAYERS = 2;
	const int MAX_AMOUNT_OF_PLAYERS = 10;

public:
	const int GetAmountOfPlayers();
	const std::string GetPlayerName(const int PlayerId);
	const int GetPlayerAction(const std::string& ActionsText, const int AmountOfActions);
	const int GetNewCardColor();


private:
	const int GetValidNumber(int& TheNumber, int MinValue, int MaxValue, std::string OptionalText = "");
};