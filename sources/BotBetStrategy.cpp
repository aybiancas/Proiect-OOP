#include "../headers/BotBetStrategy.h"
#include "../headers/Game.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

void BotBetStrategy::bet(sf::RenderWindow* window) {
	Game* game = Game::getInstance();
	std::cout << "betting round BOT enter\n";
	if (game->getBotBet()) {
		return;
	}
	int playerBet = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 500);
	playerBet = distrib(gen);
	if (playerBet > game->getPlayers()[1]->getSum()) {
		playerBet = game->getPlayers()[1]->getSum();
	}
	std::cout << "Player 2: " << playerBet << std::endl;

	game->getPlayers()[1]->subtractBet(playerBet);
	game->getPlayers()[2]->addSum(playerBet);

	sf::Text botBetText;
	botBetText.setFont(game->getFont());
	botBetText.setString("P2 bet: " + std::to_string(playerBet));
	botBetText.setCharacterSize(30);
	botBetText.setFillColor(sf::Color::White);
	botBetText.setPosition(650 - botBetText.getGlobalBounds().width / 2, 500);

	window->draw(botBetText);
	sf::sleep(sf::seconds(1));
	game->setBotBet(true);
}