
#ifndef GAME_H
#define GAME_H

#include <iostream>
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
    TableCards table;
    int roundBet;
    std::vector<std::string> handTypes;
    sf::RenderWindow* window;
    sf::Text player1Sum;
    sf::Text player2Sum;
    sf::Text textRoundBet;
    sf::Text promptText;
    std::string inputBet;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    std::vector<std::string> options;
    std::vector<sf::Text> playerOptions;
    sf::Font font;


public:

    // constructor joc
    Game();

    // constructor de copiere
    Game (const Game &other);

    // destructor
    ~Game();

    // operator =
    Game& operator=(const Game &other);

    void drawGame();

    void bettingRound();

    // aici se dau cartile playerilor, in maniera 1-2-1-2
    void dealHands();

    // repriza 1 carti
    void dealFlop();

    // reprizele 2 si 3 carti
    // turn si river puteau fi facute separat, dar e exact aceeasi cerinta
    void dealTurnRiver();

    // verifica daca sunt 5 sau mai multe de acelasi suit
    // flush, straight flush, royal flush
    bool isFlush(const std::vector<int>& suitCount);

    // verificare straight
    // straight, straight flush
    bool isStraight(const std::vector<int> &rankCount);

    int getMaxCount(const std::vector<int> &rankCount);

    bool isTwoPair(const std::vector<int> &rankCount);

    // folosita in evaluarea cartilor din mana si de pe masa
    static int getIndexRank (const std::string &rank);

    // folosita in evaluarea cartilor si de pe masa
    static int getIndexSuit (const std::string &suit);

    int highCardEvaluate (const std::vector<int> &rankCount);

    int cardGroupsEvaluate (const Player& player);

    friend std::ostream& operator<<(std::ostream& os, const Game &game);

    void resetRound();

    // functia jocului propriu zis
    void play();
};

#endif //GAME_H
