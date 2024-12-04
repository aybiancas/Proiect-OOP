
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "tableCards.h"
#include "humanPlayer.h"
#include <SFML/Graphics.hpp>
#include "botPlayer.h"
#include "dealerPlayer.h"

class Game {
    Deck deck;
    HumanPlayer player1;
    BotPlayer player2;
    DealerPlayer dealer;
    std::vector<std::unique_ptr<Player>> players;
    TableCards table;
    int roundBet;
    std::vector<std::string> handTypes;
    sf::RenderWindow* window;
    sf::Text player1Sum;
    sf::Text player2Sum;
    sf::Text textRoundBet;
    sf::Text textRoundPot;
    sf::Text promptText;
    std::string inputBet;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    std::vector<std::string> options;
    std::vector<sf::Text> playerOptions;
    sf::Font font;


public:

    Game();

    Game (const Game &other);

    ~Game();

    Game& operator=(const Game &other);

    void drawGame();

    void bettingRound();

    void updateSums();

    void resetRound();

    void dealHands();

    void dealFlop();

    void dealTurnRiver();

    static bool isFlush(const std::vector<int>& suitCount);

    static bool isStraight(const std::vector<int> &rankCount);

    static int getMaxCount(const std::vector<int> &rankCount);

    static bool isTwoPair(const std::vector<int> &rankCount);

    static int getIndexRank (const std::string &rank);

    static int getIndexSuit (const std::string &suit);

    int highCardEvaluate (const Player& player);

    int cardGroupsEvaluate (const Player& player);

    friend std::ostream& operator<<(std::ostream& os, const Game &game);

    void play();
};

#endif //GAME_H
