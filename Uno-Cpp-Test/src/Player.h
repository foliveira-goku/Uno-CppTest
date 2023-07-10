#pragma once

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include "Card.h"

class Player
{
private:
	int id{};
	bool isInUnoState{};
	std::string nickname{};
	std::string playerName{};
	std::vector<std::shared_ptr<Card::Card>> cards{};

public:
	Player() = default;
	Player(const std::string& Name,	const std::vector<std::shared_ptr<Card::Card>>& InitialCards);
	std::string_view GetName() const;
	const std::vector<std::shared_ptr<Card::Card>>& GetCards() const;
	const std::string GetInfo();
	const bool IsInUnoState() const;
	void SetId(const int NewId);
	void SetUnoState(const bool IsInUnoState);
	void ReceiveACard(const std::shared_ptr<Card::Card> NewCard);
	std::string GetAllCardsNames();
	std::shared_ptr<Card::Card> GetCardById(const int CardId);

private:
	void UpdatePlayerName();
};

