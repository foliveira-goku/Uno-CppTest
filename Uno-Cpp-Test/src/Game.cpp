#include "Game.h"

Game::Game() : playersController{inputReader.GetAmountOfPlayers()}
{
	std::srand(std::time(0));
	CreatePlayers();
}

void Game::CreatePlayers()
{
	for (int i = 0; i < playersController.GetPlayersCount(); i++)
	{
		int playerID = i + 1;
		playersController.CreatePlayer(inputReader.GetPlayerName(playerID), playerID, table.GetNewHandOfCards());
	}
}

void Game::Start()
{
	while (true)
	{
		//int option = inputReader.GetPlayerAction();
	}
}
