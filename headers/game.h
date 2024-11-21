
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "tableCards.h"


// De adaugat logica joc:
// evaluatorul de carti si definirea unui handValue pentru a decide ce grupare este mai buna
// + tiebreaker
// implementarea de ture
// ideea de call, raise, fold pentru player 1
// + functie de all in pt raise
// + caz pt call in care unul din playeri nu are suma necesara pt call -- automat fold
// automat implementare de suma pentru betting (~500/1000?) si oprirea jocului cand un player are suma = 0



class Game {
    Deck deck;
    Player player1;
    Player player2;
    TableCards table;
    int pot;
    int roundBet;
    std::vector<std::string> handTypes;

public:

    // constructor joc
    Game();

    // constructor de copiere
    Game (const Game &other);

    // destructor
    ~Game();

    // operator =
    Game& operator=(const Game &other);

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

    // functia jocului propriu zis
    void play();
};

#endif //GAME_H
