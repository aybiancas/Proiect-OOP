#include "../headers/deck.h"
#include "../headers/card.h"
#include <iostream>
#include <random>
#include <algorithm>

    Deck::Deck() :
    suits({"INIMA", "ROMB", "TREFLA", "PICA"}),
    ranks({"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}) {
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                cards.emplace_back(suit, rank);
            }
        }
        std::cout << "Deck constructor" << std::endl;
    }

    Deck::Deck (const Deck &other) : cards(other.cards) {}

    Deck::~Deck() {
        std::cout << "Deck destructor" << std::endl;
    }

    Deck& Deck::operator=(const Deck &other) {
        cards = other.cards;
        return *this;
    }

    void Deck::shuffleCards() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    std::ostream& operator<<(std::ostream &os, const Deck &deck) {
        for (const auto &card : deck.cards) {
            os << card << std::endl;
        }
        return os;
    }

    Card Deck::dealCard() {
        Card cardsDealt = cards.back();
        cards.pop_back();
        return cardsDealt;
    }

    void Deck::resetDeck() {
        cards.clear();
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                cards.emplace_back(suit, rank);
            }
        }
        shuffleCards();
    }
