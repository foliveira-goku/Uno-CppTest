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

public:
	Game();
	void Start();
	void SetupCardFunctions();

private:
	void CreatePlayers();
};

