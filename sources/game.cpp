#include <iostream>
#include "../headers/card.h"
#include "../headers/deck.h"
#include "../headers/player.h"
#include "../headers/tableCards.h"
#include "../headers/game.h"

    // constructor joc
    Game::Game() : pot(0), roundBet(0) {
        // deck ul isi da shuffle automat pentru joc, deoarece e construit ordonat
        // apelare shuffle de 5 ori de siguranta
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
    }

    // constructor de copiere
    Game::Game(const Game &other) : deck(other.deck), player1(other.player1), player2(other.player2), pot(other.pot), roundBet(other.roundBet) {}

    // destructor
    Game::~Game() {
        std::cout << "Game destructor" << std::endl;
    }

    // operator =
    Game& Game::operator=(const Game &other) {
        deck = other.deck;
        player1 = other.player1;
        player2 = other.player2;
        roundBet = other.roundBet;
        table = other.table;
        pot = other.pot;
        return *this;
    }

    // aici se dau cartile playerilor, in maniera 1-2-1-2
    void Game::dealHands() {
        for(int i = 0; i < 2; i++) {
            player1.addCard(deck.dealCard());
            player2.addCard(deck.dealCard());
        }
    }

    // repriza 1 carti
    void Game::dealFlop() {
        for(int i = 0; i < 3; i++) {
            table.addCard(deck.dealCard());
        }
    }

    // reprizele 2 si 3 carti
    // turn si river puteau fi facute separat, dar e exact aceeasi cerinta
    void Game::dealTurnRiver() {
        table.addCard(deck.dealCard());
    }


    // verifica daca sunt 5 sau mai multe de acelasi suit
    // flush, straight flush, royal flush
    bool Game::isFlush(const std::vector<int>& suitCount) {
        for (int i = 0; i < 4; i++) {
            if(suitCount[i] >= 5) {
                return true;
            }
        }
        return false;
    }

    // verificare straight
    // straight, straight flush
    bool Game::isStraight(const std::vector<int> &rankCount) {
        int counter = 0;
        for (int i = 0; i < 13; i++) {
            if(rankCount[i] > 0) {
                counter++;
            }
            else counter = 0;

            if (counter == 5) return true;
        }
        return false;
    }

    // folosita in evaluarea cartilor din mana si de pe masa
    int Game::getIndexRank(const std::string &rank) {
        if(rank == "2") return 0;
        if(rank == "3") return 1;
        if(rank == "4") return 2;
        if(rank == "5") return 3;
        if(rank == "6") return 4;
        if(rank == "7") return 5;
        if(rank == "8") return 6;
        if(rank == "9") return 7;
        if(rank == "10") return 8;
        if(rank == "J") return 9;
        if(rank == "Q") return 10;
        if(rank == "K") return 11;
        if(rank == "A") return 12;
        return -1;
    }

    // folosita in evaluarea cartilor si de pe masa
    int Game::getIndexSuit(const std::string &suit) {
        if(suit == "INIMA") return 0;
        if(suit == "ROMB") return 1;
        if(suit == "TREFLA") return 2;
        if(suit == "PICA") return 3;
        return -1;
    }

    int Game::highCardEvaluate(std::vector<Card> &cards, std::vector<int> &rankCount, std::vector<int> &suitCount) {

        int highCard = -1;
        // in functie de acel high card se va face departajarea intre playeri in cazul in care ambii au high card

        // high card iesirea default, returneaza max de carte din stash

        // for (const auto rank : ) {
        //     if (rank != 0) highCard =
        // }

        return highCard;
    }

    int Game::cardGroupsEvaluate(const Player& player) {
        // ia cartile din table si player si face 2 stash uri de carti pentru ambii playeri
        std::vector<Card> allCards = player.getPlayerCards();
        for (const auto& card : table.getTableCards()) {
            allCards.emplace_back(card);
        }

        // numarare de suit uri si rank uri in ambele grupari de 7 carti

        std::vector<int> rankCount(13, 0);
        std::vector<int> suitCount(4, 0);

        for (const auto &card : allCards) {
            int rankIndex = getIndexRank(card.getRank());
            if (rankIndex != -1) rankCount[rankIndex]++;

            int suitIndex = getIndexSuit(card.getSuit());
            if(suitIndex != -1) suitCount[suitIndex]++;
        }

        // int highCard = highCardEvaluate(allCards, rankCount, suitCount);

        int handValue = -1; // standard, in caz de e doar high card

        // royal flush = straight + flush + verif 1 dintre carti este A rankCount[13]                   value=9
        // straight flush = straight + flush                                                            value=8
        // four of a kind = counter de 4                                                                value=7
        // full house = 3 si 2, caz particular -- trebuie scoasa una dintre grupari si gasita cealalta  value=6
        // flush = flush true                                                                           value=5
        // straight = straight true                                                                     value=4
        // three of a kind = counter de 3                                                               value=3
        // two pair = 2 si 2, caz particular -- trebuie scoasa una dintre grupari si gasita cealalta    value=2
        // pair = counter de 2                                                                          value=1
        // high card = variabila separata retinuta oricum                                               value=0

        // idee: fiecare din urmatoarele if case uri poate sa retina si cartile ce intra in componenta gruparii de 5

        // pair value 1 // idee: poate include subcazuri pentru two pair si full house dupa eliminarea celor 2 carti din pair

        // two pair value 2

        // three of a kind value 3

        if (isStraight(rankCount) == true) {
            handValue = 4; // straight
        }

        if (isFlush(suitCount) == true) {
            handValue = 5; // flush
        }

        // full house value 6

        // four of a kind value 7

        if (isFlush(suitCount) == true && isStraight(rankCount) == true) {
            if (rankCount[13] != 0) handValue = 9; // royal flush
            else handValue = 8; //straight flush
        }

        // std::cout << "High card: " << highCard << std::endl;
        return handValue;

    }

    std::ostream& operator<<(std::ostream& os, const Game &game) {
        os << game.player1 << std::endl;
        os << game.player2 << std::endl;
        os << game.table << std::endl;
        return os;
    }

    // functia jocului propriu zis
    void Game::play() {

        // se dau cartile jucatorilor
        dealHands();

        // afisari de carti din mana, pur de test, vor disparea la adaugarea logicii jocului
        // (in partialitate, mana jucatorului 1 e de fapt userul care joaca)
        std::cout << std::endl << "Jucator 1:" << std::endl;
        std::cout << player1 << std::endl;

        std::cout << std::endl << "Jucator 2:" << std::endl;
        std::cout << player2 << std::endl;

        // acelasi caz ca la maini, afisari pur de test, dispar (in partialitate, cartile de pe masa oricum trebuie sa apara)
        std::cout << "Repriza 1 / Flop" << std::endl;
        dealFlop(); // adauga 3 carti pe masa
        std::cout << table << std::endl;

        // afisari test
        std::cout << "Repriza 2 / Turn" << std::endl;
        dealTurnRiver(); // adauga o carte pe masa
        std::cout << table << std::endl;

        std::cout << "Repriza 3 / River" << std::endl;
        dealTurnRiver(); // adauga o carte pe masa
        std::cout << table << std::endl;

        std::cout << "Hand Value p1: " << std::endl << cardGroupsEvaluate(player1) << std::endl;
        std::cout << "Hand value p2: " << std::endl << cardGroupsEvaluate(player2) << std::endl;

    }
