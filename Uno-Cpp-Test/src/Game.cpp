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

	SetupCardFunctions();
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
		std::shared_ptr<Card::Card> discardCard;

		bool hasBoughtACard = actionOptions.PossibleCards.size() + 1 == actionIndex ;
		bool hasSaidUno = actionOptions.PossibleCards.size() + 2 == actionIndex;
		// check if a card was bought OR if UNO was said
		if (hasBoughtACard || hasSaidUno)
		{
			if(hasBoughtACard)
			{
				auto card = table.BuyCardFromDeck();
				std::cout << "\nCard bought: " << card->GetInfo() << "\n";
				playersController.GiveCardToCurrentPlayer(card);
			}
			
			actionOptions = playersController.GetPlayerPossibleOptions(false);
			
			if(actionOptions.PossibleCards.size() <= 0)
				playersController.NextTurn();

			actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);
			discardCard = playersController.GetDiscardCardFromCurrentPlayer(actionOptions.PossibleCards[actionIndex - 1].Id);
			table.DiscardCard(discardCard);
		}
		else
		{
			discardCard = playersController.GetDiscardCardFromCurrentPlayer(actionOptions.PossibleCards[actionIndex - 1].Id);
			table.DiscardCard(discardCard);
			cardFunctions.Act(actionOptions.PossibleCards[actionIndex - 1].Type);
		}
		
		// check if didn't say uno

		playersController.NextTurn();
	}
}

void Game::SetupCardFunctions()
{
	cardFunctions.SetFunction_GetNextPlayer(
		[this]()-> std::shared_ptr<Player>&	{ 
			std::shared_ptr<Player> player = playersController.GetNextPlayer();
			return player;	
		});

	cardFunctions.SetFunction_BuyACard(
		[this]()-> std::shared_ptr<Card::Card> { return table.BuyCardFromDeck(); }
	);

	cardFunctions.SetFunction_GoToNextTurn(	[this]()-> void { return playersController.NextTurn(); });
}
