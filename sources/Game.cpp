#include <iostream>
#include <random>
#include <vector>
#include "../headers/Card.h"
#include "../headers/Deck.h"
#include "../headers/Player.h"
#include "../headers/TableCards.h"
#include "../headers/Game.h"
#include "../headers/BetInputInvalidExcept.h"
#include "../headers/FileLoadFailureExcept.h"
#include "../headers/HumanBetStrategy.h"
#include "../headers/BotBetStrategy.h"
#include "../headers/NotEnoughFundsExcept.h"

Game *Game::game = nullptr;

Game *Game::getInstance() {
	if (game == nullptr) {
		game = new Game();
	}
	return game;
}

Game::Game() : deck(),
			   roundBet(0),
			   window(nullptr),
			   inputTextCompleted(false),
			   botBet(true),
			   humanBet(true),
			   betStrategy(nullptr) {
	std::cout << "Game constructor" << std::endl;
	deck.shuffleCards();
	deck.shuffleCards();
	deck.shuffleCards();
	deck.shuffleCards();

	players.push_back(new HumanPlayer);
	players.push_back(new BotPlayer);
	players.push_back(new DealerPlayer);

	window = new sf::RenderWindow(sf::VideoMode(1300, 900), "Texas Hold' em");
	window->setFramerateLimit(20);

	if (!font.loadFromFile("fonts/BroncoPersonalUse.ttf")) {
		throw FileLoadFailure("Error: Failed to load fonts");
	}

	for (const auto &suit : deck.getSuits()) {
		for (const auto &rank : deck.getRanks()) {
			std::string key = rank + "_" + suit;
			std::string filePath = "textures/cards/" + rank + "_" + suit + ".png";
			sf::Texture texture;
			if (!texture.loadFromFile(filePath)) {
				throw FileLoadFailure("Error: could not load card file!");
			}
			cardTextures.addResource(key, texture);
		}
	}

	player1Sum.setFont(font);
	player1Sum.setString("Suma P1: " + std::to_string(players[0]->getSum()));
	player1Sum.setCharacterSize(40);
	player1Sum.setFillColor(sf::Color::White);
	player1Sum.setPosition(650 - player1Sum.getGlobalBounds().width / 2, 800);

	player2Sum.setFont(font);
	player2Sum.setString("Suma P2: " + std::to_string(players[1]->getSum()));
	player2Sum.setCharacterSize(40);
	player2Sum.setFillColor(sf::Color::White);
	player2Sum.setPosition(650 - player1Sum.getGlobalBounds().width / 2, 50);

	textRoundPot.setFont(font);
	textRoundPot.setString("Pot: " + std::to_string(players[2]->getPot()));
	textRoundPot.setCharacterSize(40);
	textRoundPot.setFillColor(sf::Color::White);
	textRoundPot.setPosition(350 - textRoundPot.getGlobalBounds().width / 2, 250);

	textRoundBet.setFont(font);
	textRoundBet.setString("Pariu curent: " + std::to_string(roundBet));
	textRoundBet.setCharacterSize(40);
	textRoundBet.setFillColor(sf::Color::White);
	textRoundBet.setPosition(650 - textRoundBet.getGlobalBounds().width / 2, 150);

	promptText.setFont(font);
	promptText.setString("Introdu o suma: ");
	promptText.setCharacterSize(40);
	promptText.setFillColor(sf::Color::White);
	promptText.setPosition(890, 400);

	inputBox.setSize(sf::Vector2f(100, 50));
	inputBox.setFillColor(sf::Color::Black);
	inputBox.setPosition(950, 450);

	inputText.setFont(font);
	inputText.setString(inputBet);
	inputText.setCharacterSize(35);
	inputText.setFillColor(sf::Color::White);
	inputText.setPosition(980, 450);
}

Game::~Game() {
	std::cout << "Game destructor" << std::endl;
}

sf::Text Game::getInputText() const {
	return inputText;
}

std::vector<Player *> &Game::getPlayers() {
	return players;
}

sf::Font Game::getFont() const {
	return font;
}

bool Game::getBotBet() const {
	return botBet;
}

void Game::setBotBet(bool botBet_) {
	this->botBet = botBet_;
}

void Game::setHumanBet(bool humanBet_) {
	this->humanBet = humanBet_;
}

void Game::setStrategy(BetStrategy* strat) {
	betStrategy = strat;
}

void Game::strategy() {
	if (betStrategy) betStrategy->bet(window);
}

void Game::handleTextInput(sf::Event &event) {
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		} else if (!inputTextCompleted && event.type == sf::Event::TextEntered) {
			if (event.text.unicode < 128) {
				// in unicode 8 este backspace
				if (event.text.unicode == 8 && inputText.getString().getSize() > 0) {
					std::string currentString = inputText.getString();
					currentString.pop_back();
					inputText.setString(currentString);
				} else if (event.text.unicode == '\r') {
					inputTextCompleted = true;
				} else {
					inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
				}
			}
		}
	}
}

void Game::drawGame() {
	window->clear(sf::Color{0, 122, 44});
	window->draw(player1Sum);
	window->draw(player2Sum);
	window->draw(textRoundPot);
	for (auto const &sprite: cardSprites) {
		window->draw(sprite);
	}
	if (!inputTextCompleted) {
		window->draw(promptText);
		window->draw(inputBox);
		window->draw(inputText);
	}

	window->display();
}

void Game::updateSums() {
	player1Sum.setString("Suma P1: " + std::to_string(players[0]->getSum()));
	player2Sum.setString("Suma P2: " + std::to_string(players[1]->getSum()));
	textRoundPot.setString("Pot: " + std::to_string(players[2]->getPot()));
}

void Game::bettingRound() {
	std::cout << "Betting round enter\n";
	if (dynamic_cast<HumanPlayer *>(players[0]) && (botBet && !humanBet)) {
		setStrategy(new HumanBetStrategy());
		strategy();
		sf::sleep(sf::seconds(1));
	} else if (dynamic_cast<BotPlayer *>(players[1]) && (!botBet && humanBet)) {
		setStrategy(new BotBetStrategy());
		strategy();
		sf::sleep(sf::seconds(1));
	} else std::cout << "Dynamic cast error\n";
}

void Game::resetRound() {
	table.clearTable();
	players[0]->clearHand();
	players[1]->clearHand();
	deck.resetDeck();
	players[2]->setSum(0);
	botBet = true;
	humanBet = true;
	inputTextCompleted = false;
	cardSprites.clear();
}

void Game::dealHands() {
	for (int i = 0; i < 2; i++) {
		players[0]->addCard(deck.dealCard());
		players[1]->addCard(deck.dealCard());
	}
}

void Game::displayHand() {
	int i = 2;
	for (auto const &card: players[0]->getPlayerCards()) {
		std::cout << card;
		std::string cardKey = card.getRank() + "_" + card.getSuit();
		sf::Sprite sprite;
		sprite.setTexture(cardTextures.getResource(cardKey));
		sprite.setPosition(100 * i, 650);
		sprite.setScale(0.25f, 0.25f);
		cardSprites.push_back(sprite);
		i++;
	}
	window->display();
}

void Game::dealFlop() {
	for (int i = 0; i < 3; i++) {
		table.addCard(deck.dealCard());
	}
}

void Game::displayFlop() {
	int i = 2;
	for (auto const &card: table.getTableCards()) {
		std::string cardKey = card.getRank() + "_" + card.getSuit();
		sf::Sprite sprite;
		sprite.setTexture(cardTextures.getResource(cardKey));
		sprite.setPosition(100 * i, 400);
		sprite.setScale(0.25f, 0.25f);
		cardSprites.push_back(sprite);
		window->draw(sprite);
		i++;
	}
	window->display();
}

void Game::dealTurnRiver() {
	table.addCard(deck.dealCard());
}

void Game::displayTurn() {
	std::string cardKey = table.getTableCards()[3].getRank() + "_" + table.getTableCards()[3].getSuit();
	sf::Sprite sprite;
	sprite.setTexture(cardTextures.getResource(cardKey));
	sprite.setPosition(100 * 5, 400);
	sprite.setScale(0.25f, 0.25f);
	cardSprites.push_back(sprite);
	window->draw(sprite);
	window->display();
}

void Game::displayRiver() {
	std::string cardKey = table.getTableCards()[4].getRank() + "_" + table.getTableCards()[4].getSuit();
	sf::Sprite sprite;
	sprite.setTexture(cardTextures.getResource(cardKey));
	sprite.setPosition(100 * 6, 400);
	sprite.setScale(0.25f, 0.25f);
	cardSprites.push_back(sprite);
	window->display();
}

bool Game::isFlush(const std::vector<int> &suitCount) {
	for (int i = 0; i < 4; i++) {
		if (suitCount[i] >= 5) {
			return true;
		}
	}
	return false;
}

bool Game::isStraight(const std::vector<int> &rankCount) {
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (rankCount[i] > 0) {
			counter++;
		} else counter = 0;

		if (counter == 5) return true;
	}
	return false;
}

int Game::getMaxCount(const std::vector<int> &rankCount) {
	int maxCount = 0;
	for (int i = 0; i < 13; i++) {
		if (rankCount[i] > maxCount) maxCount = rankCount[i];
	}
	return maxCount;
}

bool Game::isTwoPair(const std::vector<int> &rankCount) {
	int counter = 0;
	for (int i = 0; i < 13; i++) {
		if (getMaxCount(rankCount) == 2) {
			counter++;
		}
	}
	if (counter == 2) return true;
	return false;
}

int Game::getIndexRank(const std::string &rank) {
	if (rank == "2") return 0;
	if (rank == "3") return 1;
	if (rank == "4") return 2;
	if (rank == "5") return 3;
	if (rank == "6") return 4;
	if (rank == "7") return 5;
	if (rank == "8") return 6;
	if (rank == "9") return 7;
	if (rank == "10") return 8;
	if (rank == "J") return 9;
	if (rank == "Q") return 10;
	if (rank == "K") return 11;
	if (rank == "A") return 12;
	return -1;
}

int Game::getIndexSuit(const std::string &suit) {
	if (suit == "HEARTS") return 0;
	if (suit == "DIAMONDS") return 1;
	if (suit == "CLUBS") return 2;
	if (suit == "SPADES") return 3;
	return -1;
}

int Game::highCardEvaluate(const Player &player) {
	std::vector<Card> allCards = player.getPlayerCards();
	for (const auto &card: table.getTableCards()) {
		allCards.emplace_back(card);
	}

	std::vector<int> rankCount(13, 0);
	std::vector<int> suitCount(4, 0);

	for (const auto &card: allCards) {
		int rankIndex = getIndexRank(card.getRank());
		if (rankIndex != -1) rankCount[rankIndex]++;

		int suitIndex = getIndexSuit(card.getSuit());
		if (suitIndex != -1) suitCount[suitIndex]++;
	}

	int highCardVal = -1;
	for (int i = 12; i >= 0; i--) {
		if (rankCount[i]) {
			highCardVal = i;
			break;
		}
	}
	return highCardVal;
}

int Game::cardGroupsEvaluate(const Player &player) {
	std::vector<Card> allCards = player.getPlayerCards();
	for (const auto &card: table.getTableCards()) {
		allCards.emplace_back(card);
	}

	std::vector<int> rankCount(13, 0);
	std::vector<int> suitCount(4, 0);

	for (const auto &card: allCards) {
		int rankIndex = getIndexRank(card.getRank());
		if (rankIndex != -1) rankCount[rankIndex]++;

		int suitIndex = getIndexSuit(card.getSuit());
		if (suitIndex != -1) suitCount[suitIndex]++;
	}

	int handValue = 0;

	if (getMaxCount(rankCount) == 2) {
		handValue = 1; // pair
	}

	if (isTwoPair(rankCount) == true) {
		handValue = 2; // two pair
	}

	if (getMaxCount(rankCount) == 3) {
		if (handValue == 1) {
			handValue = 6; // full house
		} else handValue = 3; // three of a kind
	}

	if (isStraight(rankCount) == true) {
		handValue = 4; // straight
	}

	if (isFlush(suitCount) == true) {
		handValue = 5; // flush
	}

	if (getMaxCount(rankCount) == 4) {
		handValue = 7; // four of a kind
	}

	if (isFlush(suitCount) == true && isStraight(rankCount) == true) {
		if (rankCount[13]) handValue = 9; // royal flush
		else handValue = 8; //straight flush
	}
	return handValue;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
	os << game.players[0] << std::endl;
	os << game.players[1] << std::endl;
	os << game.players[2] << std::endl;
	os << game.table << std::endl;
	return os;
}

void Game::play() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			/*
			if (players[0]->getSum() <= 0 || players[1]->getSum() <= 0) {

				sf::Text gameOverText;
				gameOverText.setFont(font);
				gameOverText.setCharacterSize(50);
				gameOverText.setFillColor(sf::Color::White);

				if (players[0]->getSum() > 0) {
					gameOverText.setString("Game Over! Player 1 Win");
					std::cout << "Game Over! Player 1 Win" << std::endl;
				} else if (players[1]->getSum() > 0) {
					gameOverText.setString("Game Over! Player 2 Win");
					std::cout << "Game Over! Player 2 Win" << std::endl;
				} else {
					gameOverText.setString("Game Over! It's a Tie");
					std::cout << "Game Over! It's a Tie" << std::endl;
				}
				gameOverText.setPosition(650 - gameOverText.getGlobalBounds().width / 2, 300);
				window->draw(gameOverText);
				window->display();
				sf::sleep(sf::seconds(10));
				window->close();
				break;
			}
			*/
		}
		window->clear(sf::Color{0, 122, 44});

		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;

		dealHands();
		displayHand();

		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;

		humanBet = false;
		inputTextCompleted = false;
		while (!inputTextCompleted) {
			handleTextInput(event);
			drawGame();
		}
		bettingRound();
		updateSums();
		bettingRound();
		updateSums();
		std::cout << "POT: " << players[2]->getPot() << std::endl;
		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;

		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;
		std::cout << "Player input bet: " << inputBet << std::endl;
		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;


		std::cout << "ROUND 1 Flop : ";
		dealFlop();
		std::cout << table << std::endl;
		displayFlop();

		humanBet = false;
		inputTextCompleted = false;
		while (!inputTextCompleted) {
			handleTextInput(event);
			drawGame();
		}

		bettingRound();
		updateSums();
		bettingRound();
		updateSums();
		std::cout << "POT: " << players[2]->getPot() << std::endl;
		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;

		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;
		std::cout << "Player input bet: " << inputBet << std::endl;
		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;

		std::cout << "ROUND 2 Turn : ";
		dealTurnRiver();
		std::cout << table << std::endl;
		displayTurn();

		humanBet = false;
		inputTextCompleted = false;
		while (!inputTextCompleted) {
			handleTextInput(event);
			drawGame();
		}

		bettingRound();
		updateSums();
		bettingRound();
		updateSums();
		std::cout << "POT: " << players[2]->getPot() << std::endl;
		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;

		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;
		std::cout << "Player input bet: " << inputBet << std::endl;
		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;

		std::cout << "ROUND 3 River : ";
		dealTurnRiver();
		std::cout << table << std::endl;
		displayRiver();

		int handValueP1 = cardGroupsEvaluate(*players[0]);
		int handValueP2 = cardGroupsEvaluate(*players[1]);

		std::cout << "Hand Value p1: " << handValueP1 << std::endl;
		std::cout << "Hand value p2: " << handValueP2 << std::endl;

		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;


		if (handValueP1 > handValueP2) {
			std::cout << "P1 win" << std::endl;
			players[0]->addSum(players[2]->getPot());
		} else if (handValueP1 < handValueP2) {
			std::cout << "P2 win" << std::endl;
			players[1]->addSum(players[2]->getPot());
		} else {
			int highCardP1 = highCardEvaluate(*players[0]);
			int highCardP2 = highCardEvaluate(*players[1]);

			if (highCardP1 > highCardP2) {
				std::cout << "P1 win" << std::endl;
				players[0]->addSum(players[2]->getPot());
			} else if (highCardP1 < highCardP2) {
				std::cout << "P2 win" << std::endl;
				players[1]->addSum(players[2]->getPot());
			} else {
				std::cout << "Tie" << std::endl;
				players[0]->addSum((players[2]->getPot()) / 2);
				players[1]->addSum((players[2]->getPot()) / 2);
			}
		}
		std::cout << std::endl << "Player 1 sum: " << players[0]->getSum() << std::endl;
		std::cout << std::endl << "Player 2 sum: " << players[1]->getSum() << std::endl;
		if (players[0]->getSum() <= 0 || players[1]->getSum() <= 0) {
			if (players[0]->getSum() > 0) {
				std::cout << "P1 overall win" << std::endl;
			} else if (players[1]->getSum() > 0) {
				std::cout << "P2 overall win" << std::endl;
			} else std::cout << "Overall Tie" << std::endl;
			break;
		}
		resetRound();
		std::cout << "Human bool bet: " << humanBet << "  Bot bool bet: " << botBet << std::endl;
	}
}
