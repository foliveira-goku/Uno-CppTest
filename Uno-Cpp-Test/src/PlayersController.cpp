#include "PlayersController.h"

PlayersController::PlayersController(const int AmountOfPlayers)
{
	players.reserve(AmountOfPlayers);
}

void PlayersController::SetFunction_GetCurrentDiscardCard
(const std::function<std::shared_ptr<Card::Card>& ()>& Function)
{
	function_GetCurrentDiscardCard = Function;
}

void PlayersController::CreatePlayer(const std::string& Name,
	const std::vector<std::shared_ptr<Card::Card>>& Cards)
{
	players.emplace_back(new Player{ Name, Cards });
}

void PlayersController::ReservePlayersOrder()
{
	std::reverse(players.begin(), players.end()); 
	currentPlayerIndex = players.size() - 1 - currentPlayerIndex;
}

void PlayersController::GiveCardToPlayer(const std::shared_ptr<Card::Card> Card,
	const PlayerSelection::Options ChosenPlayer)
{
	players[GetPlayerIndex(ChosenPlayer)]->ReceiveACard(Card);
}

std::shared_ptr<Card::Card> PlayersController::GetPlayerCardById(const int CardId,
	const PlayerSelection::Options PlayerChoice)
{
	return players[GetPlayerIndex(PlayerChoice)]->GetCardById(CardId);
}

std::string_view PlayersController::GetPlayerName(const PlayerSelection::Options PlayerChoice) const
{ 
	return players[GetPlayerIndex(PlayerChoice)]->GetName();
}

const int PlayersController::GetPlayersCount() const { return players.capacity(); }

PlayerOptions PlayersController::GetPlayerPossibleOptions(const bool CanBuyCard) const
{
	auto currentPlayer = players[currentPlayerIndex];
	auto currentPlayerCards = currentPlayer->GetCards();
	PlayerOptions playerOptions{};
	std::string tempOption{}; // não sou fã, mas...
	
	playerOptions.OptionsText = currentPlayer->GetInfo();
	playerOptions.OptionsText.append("\nChoose an option: \n|");

	auto currentDiscardCard = function_GetCurrentDiscardCard();
	
	
	for (int i = 0; i < currentPlayerCards.size(); i++)
	{
		// Compare cards
		if (!AreCardsCompatible(currentDiscardCard, currentPlayerCards[i]))
			continue;

		playerOptions.PossibleCards.push_back({ currentPlayerCards[i]->GetId(), currentPlayerCards[i]->GetType() });
		playerOptions.OptionsCount++;
		
		tempOption = std::format(PlayerOptionFormat, playerOptions.OptionsCount, currentPlayerCards[i]->GetInfo());
		playerOptions.OptionsText.append(tempOption);
	}

	if (CanBuyCard)
	{
		playerOptions.OptionsCount++;
		tempOption = std::format(PlayerOptionFormat, playerOptions.OptionsCount, "Buy a card");
		playerOptions.OptionsText.append(tempOption);
	}

	bool canSayUno = currentPlayerCards.size() == 2 && 
					 playerOptions.PossibleCards.size() > 0 &&
					 !currentPlayer->IsInUnoState();
	if (canSayUno)
	{
		playerOptions.OptionsCount++;
		tempOption = std::format(PlayerOptionFormat, playerOptions.OptionsCount, "UNO!");
		playerOptions.OptionsText.append(tempOption);
	}

	return playerOptions;
}

const bool PlayersController::NextPlayerHasPlusTwo() const
{
	auto cards = players[GetPlayerIndex(PlayerSelection::Next)]->GetCards();

	for (std::shared_ptr<Card::Card>& card : cards)
	{
		if (card->GetType() == Card::Type::PlusTwo)
			return true;
	}

	return false;
}

PlayerOptions PlayersController::GetNextPlayerPossiblePlusTwoOptions(bool _) const
{
	auto nextPlayer = players[GetPlayerIndex(PlayerSelection::Next)];
	auto nextPlayerCards = nextPlayer->GetCards();
	PlayerOptions playerOptions{};

	playerOptions.OptionsText = nextPlayer->GetInfo();
	playerOptions.OptionsText.append("\nChoose an option: \n| ");

	for (int i = 0; i < nextPlayerCards.size(); i++)
	{
		if (nextPlayerCards[i]->GetType() == Card::Type::PlusTwo)
		{
			playerOptions.PossibleCards.push_back({ nextPlayerCards[i]->GetId(), nextPlayerCards[i]->GetType() });
			playerOptions.OptionsCount++;
			playerOptions.OptionsText.append("[").append(std::to_string(playerOptions.OptionsCount)).append("] ")
									 .append(nextPlayerCards[i]->GetInfo()).append(" | ");
		}
	}

	bool canSayUno = nextPlayerCards.size() == 2 &&
		playerOptions.PossibleCards.size() > 0 &&
		!nextPlayer->IsInUnoState();
	if (canSayUno)
	{
		playerOptions.OptionsCount++;
		playerOptions.OptionsText.append("[").append(std::to_string(playerOptions.OptionsCount)).append("] UNO! |");
	}

	return playerOptions;
}

const bool PlayersController::IsPlayerInUnoState(const PlayerSelection::Options PlayerChoice) const
{	
	return players[GetPlayerIndex(PlayerChoice)]->IsInUnoState();
}

const int PlayersController::GetPlayerCardsCount(const PlayerSelection::Options PlayerChoice) 
{
	return players[GetPlayerIndex(PlayerChoice)]->GetCards().size();
}

void PlayersController::SetPlayerUnoState(const bool IsInUnoState, const PlayerSelection::Options PlayerChoice)
{ players[GetPlayerIndex(PlayerChoice)]->SetUnoState(IsInUnoState); }

void PlayersController::ShufflePlayersAndSetId()
{
	RandomHelper::SuffleVector<std::shared_ptr<Player>>(players);

	for (int i = 0; i < players.size(); i++)
		players[i]->SetId(i+1);
}

void PlayersController::GoToNextTurn()
{
	currentPlayerIndex = GetPlayerIndex(PlayerSelection::Next);
}

bool PlayersController::AreCardsCompatible(const std::shared_ptr<Card::Card>& DiscardCard, 
										   const std::shared_ptr<Card::Card>& OtherCard) const
{
	if (OtherCard->GetColor() == Card::Color::Black)
		return true;

	if (DiscardCard->GetColor() == OtherCard->GetColor())
		return true;

	if (DiscardCard->GetType() == OtherCard->GetType())
	{
		// Reminder: cards with NO number has a 'Number' value of -1, so this 'if' works for them too.
		if (DiscardCard->GetNumber() == OtherCard->GetNumber())
			return true;

		return false;
	}

	return false;
}

int PlayersController::GetPlayerIndex(const PlayerSelection::Options Choice) const
{	
	return (currentPlayerIndex + Choice) % players.size();
}