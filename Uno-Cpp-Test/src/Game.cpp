#include "Game.h"

Game::Game() : playersController{ inputReader.GetAmountOfPlayers() }
{
	RandomHelper::Initialize();
	CreatePlayers();
	playersController.ShufflePlayersAndSetId();
	table.DiscardFirstCard();

	playersController.SetFunction_GetCurrentDiscardCard
	(
		[this]()-> std::shared_ptr<Card::Card>& { return table.GetCurrentDiscardCard(); }
	);

	SetupCardFunctions();
}

void Game::CreatePlayers()
{
	int playerCount{};
	for (int i = 0; i < playersController.GetPlayersCount(); i++)
	{
		playerCount = i + 1;
		playersController.CreatePlayer(inputReader.GetPlayerName(playerCount), table.GetNewHandOfCards());
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

		bool hasBoughtACard = actionOptions.PossibleCards.size() + 1 == actionIndex;
		bool hasSaidUno = actionOptions.PossibleCards.size() + 2 == actionIndex;
		// check if a card was bought OR if UNO was said
		if (hasBoughtACard || hasSaidUno)
		{
			if (hasBoughtACard)
			{
				auto card = table.BuyCardFromDeck();
				std::cout << "\nCard bought: " << card->GetInfo() << "\n";
				playersController.GiveCardToCurrentPlayer(card);
			}

			if (hasSaidUno)
			{
				std::cout << "\n\n" << playersController.GetCurrentPlayerName() << "says UNO!\n\n";
				playersController.SetCurrentPlayerUnoState(true);
			}

			std::cout << "\nCurrent discard card: " << table.GetCurrentDiscardCard()->GetInfo() << "\n";

			actionOptions = playersController.GetPlayerPossibleOptions(false);

			if (actionOptions.PossibleCards.size() <= 0)
			{
				std::cout << "\nThere is no card to be discarded...\n";
				playersController.NextTurn();
				continue;
			}

			actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);
		}

		discardCard = playersController.GetDiscardCardFromCurrentPlayer(actionOptions.PossibleCards[actionIndex - 1].Id);
		table.DiscardCard(discardCard);

		int playerCardsCount = playersController.GetCurrentPlayerCardsCount();
		if (playerCardsCount <= 0)
		{
			std::cout << "\n" << playersController.GetCurrentPlayerName() << " has won the game!!!\n";
			return;
		}

		bool didntSayUno = playerCardsCount == 1 && !playersController.IsCurrentPlayerInUnoState();
		if (didntSayUno)
		{
			std::cout << "\n" << playersController.GetCurrentPlayerName() << " didn't say UNO!\n";
			auto cardA = table.BuyCardFromDeck();
			auto cardB = table.BuyCardFromDeck();
			playersController.GiveCardToCurrentPlayer(cardA);
			playersController.GiveCardToCurrentPlayer(cardB);

			playersController.SetCurrentPlayerUnoState(false);
		}

		cardFunctions.Act(actionOptions.PossibleCards[actionIndex - 1].Type);

		playersController.NextTurn();
	}
}

void Game::SetupCardFunctions()
{
	cardFunctions.SetFunction_GetNextPlayer(
		[this]()-> std::shared_ptr<Player>&
		{
			std::shared_ptr<Player> player = playersController.GetNextPlayer();
			return player;
		});

	cardFunctions.SetFunction_BuyACard(
		[this]()-> std::shared_ptr<Card::Card> { return table.BuyCardFromDeck(); }
	);

	cardFunctions.SetFunction_GoToNextTurn([this]()-> void { return playersController.NextTurn(); });

	cardFunctions.SetFunction_ReversePlayersOrder([this]()-> void { return playersController.ReservePlayersOrder(); });
}
