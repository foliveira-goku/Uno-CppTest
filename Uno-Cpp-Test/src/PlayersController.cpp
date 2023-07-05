#include "PlayersController.h"

PlayersController::PlayersController(const int AmountOfPlayers)
{
	players.reserve(AmountOfPlayers);
}

void PlayersController::SetFunction_GetCurrentDiscardCard
(const std::function<std::shared_ptr<Card::Card>& ()>& Function)
{
	getCurrentDiscardCardFunction = Function;
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

void PlayersController::GiveCardToCurrentPlayer(const std::shared_ptr<Card::Card> card)
{
	players[currentPlayerIndex]->ReceiveACard(card);
}

std::shared_ptr<Card::Card> PlayersController::GetDiscardCardFromCurrentPlayer(const int CardId)
{
	return players[currentPlayerIndex]->GetCardToDiscard(CardId);
}

void PlayersController::NextTurn() 
{
	currentPlayerIndex = GetNextPlayerIndex(); 
}

const std::shared_ptr<Player>& PlayersController::GetNextPlayer() const
{
	return players[GetNextPlayerIndex()];
}

const std::string PlayersController::GetCurrentPlayerName() const
{ 
	return players[currentPlayerIndex]->GetName(); 
}

const int PlayersController::GetPlayersCount() const { return players.capacity(); }

//TODO refactor this!
const PlayerOptions PlayersController::GetPlayerPossibleOptions(const bool CanBuyCard) const
{
	auto currentPlayer = players[currentPlayerIndex];
	auto currentPlayerCards = currentPlayer->GetCards();
	PlayerOptions playerOptions{};

	playerOptions.OptionsText = currentPlayer->GetInfo();
	playerOptions.OptionsText += "\nChoose an option: \n| ";

	auto currentDiscardCard = getCurrentDiscardCardFunction();

	for (int i = 0; i < currentPlayerCards.size(); i++)
	{
		// Compare cards
		if (!AreCardsCompatible(currentDiscardCard, currentPlayerCards[i]))
			continue;

		playerOptions.PossibleCards.push_back({ currentPlayerCards[i]->GetId(), currentPlayerCards[i]->GetType() });
		playerOptions.OptionsCount++;
		playerOptions.OptionsText += "[" + std::to_string(playerOptions.OptionsCount) + "] " + currentPlayerCards[i]->GetInfo() + " | ";
	}

	if (CanBuyCard)
	{
		playerOptions.OptionsCount++;
		playerOptions.OptionsText += "[" + std::to_string(playerOptions.OptionsCount) + "] Buy a card | ";
	}

	bool canSayUno = currentPlayerCards.size() == 2 && 
					 playerOptions.PossibleCards.size() > 0 &&
					 !currentPlayer->IsInUnoState();
	if (canSayUno)
	{
		playerOptions.OptionsCount++;
		playerOptions.OptionsText += "[" + std::to_string(playerOptions.OptionsCount) + "] UNO! |";
	}

	return playerOptions;
}

const bool PlayersController::IsCurrentPlayerInUnoState() {	return players[currentPlayerIndex]->IsInUnoState(); }

const int PlayersController::GetCurrentPlayerCardsCount() { return players[currentPlayerIndex]->GetCards().size(); }

void PlayersController::SetCurrentPlayerUnoState(const bool IsInUnoState) 
{ players[currentPlayerIndex]->SetUnoState(IsInUnoState); }

void PlayersController::ShufflePlayersAndSetId()
{
	RandomHelper::SuffleVector<std::shared_ptr<Player>>(players);

	for (int i = 0; i < players.size(); i++)
		players[i]->SetId(i+1);
}

bool PlayersController::AreCardsCompatible(std::shared_ptr<Card::Card>& DiscardCard, std::shared_ptr<Card::Card>& OtherCard) const
{
	if (OtherCard->GetColor() == Card::Color::Black)
		return true;

	if (DiscardCard->GetColor() == OtherCard->GetColor())
		return true;

	if (DiscardCard->GetType() == OtherCard->GetType())
	{
		// Reminder: cards with NO number has a 'Number' value of -1, so this if works for them too.
		if (DiscardCard->GetNumber() == OtherCard->GetNumber())
			return true;

		return false;
	}

	return false;
}

int PlayersController::GetNextPlayerIndex() const {	return (currentPlayerIndex + 1) % players.size(); }