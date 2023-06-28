#pragma once

#include "InputReader.h"
#include "PlayersController.h"
#include "Table.h"

class Game
{
private:
	Table table{};
	InputReader inputReader{};
	PlayersController playersController{};

public:
	Game();
	void Start();

private:
	void CreatePlayers();
};

