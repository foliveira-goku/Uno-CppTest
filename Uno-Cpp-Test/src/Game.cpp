#include "Game.h"

Game::Game() : playersController{ inputReader.GetAmountOfPlayers() }
{
	std::srand(std::time(0));
	CreatePlayers();
	table.DiscardFirstCard();

	playersController.SetFunction_GetCurrentDiscardCard
	(
		[this]()-> std::shared_ptr<Card::Card>& { return table.GetCurrentDiscardCard(); }
	);
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
	std::cout << "\n\n\nStarting the game...";

	while (true)
	{
		std::cout << "\n\n\nCurrent player: " << playersController.GetCurrentPlayerName() << "\n";
		std::cout << "\nCurrent discard card: " << table.GetCurrentDiscardCard()->GetInfo() << "\n";

		PlayerOptions actionOptions = playersController.GetPlayerPossibleOptions();

		int actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);

		// CardFunctions.Act(actionOptions.PossibleCards[actionIndex - 1])

		std::cout << "Action chosen: " << actionIndex << std::endl;

		playersController.NextTurn();
	}
}
