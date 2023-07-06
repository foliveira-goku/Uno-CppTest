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

	GetPlayerPossibleOptions = [this](bool canBuyCard) -> PlayerOptions
	{
		PlayerOptions options = playersController.GetPlayerPossibleOptions(canBuyCard);
		return options;
	};

	GetPlayerPossiblePlusTwoOptions = [this](bool _) -> PlayerOptions
	{
		PlayerOptions options = playersController.GetNextPlayerPossiblePlusTwoOptions(_);
		return options;
	};

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

void Game::BuyCardsForPlayer(const int Amount)
{
	for (int i = 0; i < Amount; i++)
	{
		auto card = table.BuyCardFromDeck();
		std::cout << "\nCard bought: " << card->GetInfo() << "\n";
		playersController.GiveCardToCurrentPlayer(card);
	}
}

void Game::SayUno()
{
	std::cout << "\n\n" << playersController.GetCurrentPlayerName() << "says UNO!\n\n";
	playersController.SetCurrentPlayerUnoState(true);
}

const bool Game::CheckIfHasValidCard(const int AmountOfPossibleActions)
{
	if (AmountOfPossibleActions <=0)
	{
		std::cout << "\nThere is no card to be discarded...\n";
		return false;
	}

	return true;
}

const bool Game::CheckIfPlayerHasWonTheGame(const int AmountOfCards)
{
	if (AmountOfCards <= 0)
	{
		std::cout << "\n" << playersController.GetCurrentPlayerName() << " has won the game!!!\n";
		return true;
	}
	return false;
}

const bool Game::CheckIfDidntSayUno(const int AmountOfCards)
{
	if (AmountOfCards == 1 && !playersController.IsCurrentPlayerInUnoState())
	{
		std::cout << "\n" << playersController.GetCurrentPlayerName() << " didn't say UNO!\n";
		return true;
	}
	return false;
}

void Game::ShowCurrentDiscardCard()
{
	std::cout << "\nCurrent discard card: " << table.GetCurrentDiscardCard()->GetInfo() << "\n";
}

void Game::SetupCardFunctions()
{
	cardFunctions.SetFunction_GetNextPlayerName(
		[this]()-> const std::string
		{
			return playersController.GetNextPlayerName();
		});

	cardFunctions.SetFunction_BuyACard(
		[this]()-> std::shared_ptr<Card::Card> { return table.BuyCardFromDeck(); }
	);

	cardFunctions.SetFunction_GoToNextTurn([this]()-> void { playersController.NextTurn(); });

	cardFunctions.SetFunction_ReversePlayersOrder([this]()-> void { playersController.ReservePlayersOrder(); });

	cardFunctions.SetFunction_NextPlayerHasPlusTwo([this]()-> const bool { return playersController.NextPlayerHasPlusTwo(); });

	cardFunctions.SetFunction_ProcessNextPlayerPlusTwoTurn([this]() -> void {
			int chosenCardId = ProcessPlayerActionChoise(GetPlayerPossiblePlusTwoOptions, false);
			table.DiscardCard(playersController.GetNextPlayerCardById(chosenCardId));
		});

	cardFunctions.SetFunction_GiveCardToPlayer([this](std::shared_ptr<Card::Card> Card)-> void {
			playersController.GiveCardToNextPlayer(Card);
		});

	cardFunctions.SetFunction_GetPlayerColorInput([this]()-> Card::Color {
			return static_cast<Card::Color>(inputReader.GetNewCardColor());
		});

	cardFunctions.SetFunction_ChangeCurrentCardColor([this](Card::Color NewColor)-> void { 
		auto card = table.GetCurrentDiscardCard();
		card->ChangeColor(NewColor);
	});
}

void Game::Start()
{
	std::cout << "\n\n\nStarting the game...";

	while (true)
	{
		std::string name = playersController.GetCurrentPlayerName();
		std::cout << "\n\n\nCurrent player: " << name << "\n";
		ShowCurrentDiscardCard();

		int chosenCardId = ProcessPlayerActionChoise(GetPlayerPossibleOptions, true);

		if (chosenCardId < 0)
		{
			playersController.NextTurn();
			continue;
		}

		std::shared_ptr<Card::Card> discardCard = playersController.GetPlayerCardById(chosenCardId);
		Card::Type discardCardType = discardCard->GetType();
		
		table.DiscardCard(discardCard);

		int playerCardsCount = playersController.GetCurrentPlayerCardsCount();
		if (CheckIfPlayerHasWonTheGame(playerCardsCount))
			return;

		if (CheckIfDidntSayUno(playerCardsCount))
		{
			BuyCardsForPlayer(2);
			playersController.SetCurrentPlayerUnoState(false);
		}

		cardFunctions.Act(discardCardType);

		playersController.NextTurn();
	}
}

const int Game::ProcessPlayerActionChoise(const std::function<PlayerOptions (const bool)>& GetPlayerOptions, 
	const bool CanBuyCard)
{
	auto actionOptions = GetPlayerOptions(CanBuyCard);
	int actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);

	int possibleCardsAmount = actionOptions.PossibleCards.size();
	// check if a card was bought OR if UNO was said
	if (actionIndex > possibleCardsAmount)
	{
		if (CanBuyCard)
		{
			bool hasBoughtACard = possibleCardsAmount + 1 == actionIndex;
			if (hasBoughtACard)
				BuyCardsForPlayer(1);
			else
				SayUno();
		}
		else
			SayUno();

		ShowCurrentDiscardCard();

		actionOptions = GetPlayerOptions(false);

		if (!CheckIfHasValidCard(actionOptions.PossibleCards.size()))
			return -1;

		actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);
	}

	return actionOptions.PossibleCards[actionIndex - 1].Id;
}