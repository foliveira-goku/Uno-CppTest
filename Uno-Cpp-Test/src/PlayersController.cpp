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

PlayerOptions PlayersController::GetPlayerPossibleOptions(PlayerSelection::Options PlayerChoice, const bool CanBuyCard,
	const bool CheckForPlusTwo) // <- this boolean is ugly but it was the easest way to do it
{
	std::shared_ptr<Player> chosenPlayer = players[GetPlayerIndex(PlayerChoice)];
	std::vector<std::shared_ptr<Card::Card>> currentPlayerCards = chosenPlayer->GetCards();
	PlayerOptions playerOptions{ 0, chosenPlayer->GetInfo(), {} };
	std::string formatedOptionText{};
	
	playerOptions.OptionsText.append("\nChoose an option: \n|");

	std::shared_ptr<Card::Card> currentDiscardCard = function_GetCurrentDiscardCard();
	
	AddPossibleCardsToPlayerOptions(playerOptions, currentDiscardCard, currentPlayerCards, CheckForPlusTwo);

	if (CanBuyCard)
	{
		playerOptions.OptionsCount++;
		formatedOptionText = std::format(PlayerOptionFormat, playerOptions.OptionsCount, BuyACardText);
		playerOptions.OptionsText.append(formatedOptionText);
	}

	bool canSayUno = currentPlayerCards.size() == 2 && 
					 playerOptions.PossibleCards.size() > 0 &&
					 !chosenPlayer->IsInUnoState();
	if (canSayUno)
	{
		playerOptions.OptionsCount++;
		formatedOptionText = std::format(PlayerOptionFormat, playerOptions.OptionsCount, UnoText);
		playerOptions.OptionsText.append(formatedOptionText);
	}

	return playerOptions;
}

void PlayersController::AddPossibleCardsToPlayerOptions(PlayerOptions& PlayerOptions, const std::shared_ptr<Card::Card>& CurrentDiscardCard,
	const std::vector<std::shared_ptr<Card::Card>>& CurrentPlayerCards, const bool CheckForPlusTwo)
{
	std::string formatedOptionText{};

	for (int i = 0; i < CurrentPlayerCards.size(); i++)
	{
		if (!AreCardsCompatible(CurrentDiscardCard, CurrentPlayerCards[i]))
			continue;

		if (CheckForPlusTwo && CurrentPlayerCards[i]->GetType() != Card::Type::PlusTwo)
			continue;

		PlayerOptions.PossibleCards.push_back({ CurrentPlayerCards[i]->GetId(), CurrentPlayerCards[i]->GetType() });
		PlayerOptions.OptionsCount++;

		formatedOptionText = std::format(PlayerOptionFormat, PlayerOptions.OptionsCount, CurrentPlayerCards[i]->GetInfo());
		PlayerOptions.OptionsText.append(formatedOptionText);
	}
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