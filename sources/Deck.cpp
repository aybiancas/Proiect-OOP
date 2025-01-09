#include "../headers/Deck.h"
#include "../headers/Card.h"
#include "../headers/FileLoadFailureExcept.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <memory>

Deck::Deck() :
    suits({"HEARTS", "DIAMONDS", "CLUBS", "SPADES"}),
    ranks({"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}) {
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                Card card(suit, rank);
                cards.emplace_back(card);
            }
        }
        std::cout << "Deck constructor" << std::endl;
    }

    // Deck::Deck (const Deck &other) : cards(other.cards) {}

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
                Card card(suit, rank);
                cards.emplace_back(card);
            }
        }
        shuffleCards();
    }

std::vector<std::string> Deck::getSuits() const {
    return suits;
}

std::vector<std::string> Deck::getRanks() const {
    return ranks;
}
