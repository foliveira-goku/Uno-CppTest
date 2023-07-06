#pragma once

#include <functional>
#include "InputReader.h"
#include "PlayersController.h"
#include "Table.h"
#include "CardFunctions.h"

class Game
{
private:
	Table table{};
	InputReader inputReader{};
	PlayersController playersController{};
	CardFunctions cardFunctions{};
	std::function<PlayerOptions (const bool)> GetPlayerPossibleOptions;
	std::function<PlayerOptions (const bool)> GetPlayerPossiblePlusTwoOptions;
public:
	Game();
	void Start();

private:
	const int ProcessPlayerActionChoise(const std::function<PlayerOptions (const bool)>& GetPlayerOptions, const bool CanBuyCard);
	const bool CheckIfHasValidCard(const int AmountOfPossibleActions);
	const bool CheckIfPlayerHasWonTheGame(const int AmountOfCards);
	const bool CheckIfDidntSayUno(const int AmountOfCards);
	void ShowCurrentDiscardCard();
	void BuyCardsForPlayer(const int Amount);
	void SayUno();
	void SetupCardFunctions();
	void CreatePlayers();
};

