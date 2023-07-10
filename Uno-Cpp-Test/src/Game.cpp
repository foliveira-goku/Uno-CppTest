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
		PlayerOptions options = playersController.GetPlayerPossibleOptions(
								PlayerSelection::Current, canBuyCard, false);
		return options;
	};

	GetNextPlayerPossiblePlusTwoOptions = [this](bool _) -> PlayerOptions
	{
		PlayerOptions options = playersController.GetPlayerPossibleOptions(
								PlayerSelection::Next, false, true);
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

void Game::SetupCardFunctions()
{
	cardFunctions.SetFunction_GetPlayerName(
		[this](PlayerSelection::Options PlayerChoice)-> std::string_view { return playersController.GetPlayerName(PlayerChoice);});

	cardFunctions.SetFunction_BuyACard([this]()-> std::shared_ptr<Card::Card> { return table.BuyCardFromDeck(); });

	cardFunctions.SetFunction_GoToNextTurn([this]()-> void { playersController.GoToNextTurn(); });

	cardFunctions.SetFunction_ReversePlayersOrder([this]()-> void { playersController.ReservePlayersOrder(); });

	cardFunctions.SetFunction_NextPlayerHasPlusTwo([this]()-> const bool { return playersController.NextPlayerHasPlusTwo(); });

	cardFunctions.SetFunction_ProcessNextPlayerPlusTwoTurn(
		[this]() -> void
		{
			int chosenCardId = ProcessPlayerActionChoise(GetNextPlayerPossiblePlusTwoOptions, false);
			table.DiscardCard(playersController.GetPlayerCardById(chosenCardId, PlayerSelection::Next));
		});

	cardFunctions.SetFunction_GiveCardToPlayer(
		[this](std::shared_ptr<Card::Card> Card,PlayerSelection::Options PlayerChoise)-> void	
		{ playersController.GiveCardToPlayer(Card, PlayerChoise); });

	cardFunctions.SetFunction_GetPlayerColorInput(
		[this]()-> Card::Color {return static_cast<Card::Color>(inputReader.GetNewCardColor()); });

	cardFunctions.SetFunction_ChangeCurrentCardColor(
		[this](Card::Color NewColor)-> void	
		{
			auto card = table.GetCurrentDiscardCard();
			card->ChangeColor(NewColor);
		});
}

void Game::Start()
{
	std::cout << "\n\n\nStarting the game...";

	while (true)
	{
		std::cout << "\n\n\nCurrent player: " << playersController.GetPlayerName(PlayerSelection::Current) << "\n";
		ShowCurrentDiscardCard();

		int chosenCardId = ProcessPlayerActionChoise(GetPlayerPossibleOptions, true);

		if (chosenCardId < 0)
		{
			playersController.GoToNextTurn();
			continue;
		}

		std::shared_ptr<Card::Card> discardCard = playersController.GetPlayerCardById(chosenCardId, PlayerSelection::Current);
		Card::Type discardCardType = discardCard->GetType();

		table.DiscardCard(discardCard);

		int playerCardsCount = playersController.GetPlayerCardsCount(PlayerSelection::Current);
		if (CheckIfPlayerHasWonTheGame(playerCardsCount))
			return;

		if (CheckIfDidntSayUno(playerCardsCount))
		{
			BuyCardsForPlayer(2);
			playersController.SetPlayerUnoState(false, PlayerSelection::Current);
		}

		cardFunctions.Act(discardCardType);

		playersController.GoToNextTurn();
	}
}

void Game::BuyCardsForPlayer(const int Amount)
{
	for (int i = 0; i < Amount; i++)
	{
		auto card = table.BuyCardFromDeck();
		std::cout << "\nCard bought: " << card->GetInfo() << "\n";
		playersController.GiveCardToPlayer(card, PlayerSelection::Current);
	}
}

void Game::SayUno()
{
	std::cout << "\n\n" << playersController.GetPlayerName(PlayerSelection::Current) << "says UNO!\n\n";
	playersController.SetPlayerUnoState(true, PlayerSelection::Current);
}

const bool Game::CheckIfPlayerHasWonTheGame(const int AmountOfCards)
{
	if (AmountOfCards <= 0)
	{
		std::cout << "\n" << playersController.GetPlayerName(PlayerSelection::Current) << " has won the game!!!\n";
		return true;
	}
	return false;
}

const bool Game::CheckIfDidntSayUno(const int AmountOfCards)
{
	if (AmountOfCards == 1 && !playersController.IsPlayerInUnoState(PlayerSelection::Current))
	{
		std::cout << "\n" << playersController.GetPlayerName(PlayerSelection::Current) << " didn't say UNO!\n";
		return true;
	}
	return false;
}

void Game::ShowCurrentDiscardCard()
{
	std::cout << "\nCurrent discard card: " << table.GetCurrentDiscardCard()->GetInfo() << "\n\n";
}

const int Game::ProcessPlayerActionChoise(const std::function<PlayerOptions(const bool)>& GetPlayerOptions, 
	const bool CanBuyCard)
{
	auto actionOptions = GetPlayerOptions(CanBuyCard);
	int actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);

	int possibleCardsAmount = actionOptions.PossibleCards.size();

	if (actionIndex > possibleCardsAmount)
	{
		actionOptions = HandleExtraOptions(possibleCardsAmount, actionIndex, CanBuyCard, GetPlayerOptions);
		possibleCardsAmount = actionOptions.PossibleCards.size();

		if (possibleCardsAmount <= 0)
		{
			std::cout << "\nThere is no card to be discarded...\n";
			return -1;
		}

		actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);

		bool saidUnoAfterBuyingACard = actionIndex > possibleCardsAmount;
		if (saidUnoAfterBuyingACard)
		{
			SayUno();
			actionOptions = GetPlayerOptions(false);
			actionIndex = inputReader.GetPlayerAction(actionOptions.OptionsText, actionOptions.OptionsCount);
		}
	}

	return actionOptions.PossibleCards[actionIndex - 1].Id;
}

PlayerOptions Game::HandleExtraOptions(const int PossibleCardsAmount, const int ChosenActionIndex, const bool CanBuyCard,
	const std::function<PlayerOptions(const bool)>& GetPlayerOptions)
{
	if (CanBuyCard && PossibleCardsAmount + 1 == ChosenActionIndex)
	{
		BuyCardsForPlayer(1);
		playersController.SetPlayerUnoState(false, PlayerSelection::Current);
	}
	else
		SayUno();

	ShowCurrentDiscardCard();

	return GetPlayerOptions(false);
}