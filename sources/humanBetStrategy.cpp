#include "../headers/HumanBetStrategy.h"
#include "../headers/game.h"
#include "../headers/BetInputInvalidExcept.h"
#include "../headers/NotEnoughFundsExcept.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

void HumanBetStrategy::bet(sf::RenderWindow *window) {
	Game* game = Game::getInstance();
	std::cout << "Betting round: Human enter\n";
	std::string inputBet = game->getInputText().getString().toAnsiString();
	std::cout << inputBet;
	int playerBet = 0;
	try {
		playerBet = std::stoi(inputBet);
		std::cout << "Player betting: " << playerBet << std::endl;
	} catch (const std::invalid_argument &) {
		std::cout << "Invalid input\n";
		return;
	}
	if (playerBet > game->getPlayers()[0]->getSum()) {
		throw NotEnoughFundsExcept("Error: the player does not have enough credits for this bet");
	}
	if (playerBet < 0) {
		throw BetInputInvalidExcept("Error: bet value is invalid");
	}
	game->getPlayers()[0]->subtractBet(playerBet);
	game->getPlayers()[2]->addSum(playerBet);

	sf::Text playerBetText;
	playerBetText.setFont(game->getFont());
	playerBetText.setString("P1 Bet: " + std::to_string(playerBet));
	playerBetText.setCharacterSize(30);
	playerBetText.setFillColor(sf::Color::White);
	playerBetText.setPosition(650 - playerBetText.getGlobalBounds().width / 2, 300);

	window->draw(playerBetText);
	sf::sleep(sf::seconds(1));

	game->setBotBet(false);
	game->setHumanBet(true);
}
