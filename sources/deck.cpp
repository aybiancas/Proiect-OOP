#include "../headers/deck.h"
#include "../headers/card.h"
#include "../headers/FileLoadFailureExcept.h"
#include <iostream>
#include <random>
#include <algorithm>

    Deck::Deck() :
    suits({"HEARTS", "DIAMONDS", "CLUBS", "SPADES"}),
    ranks({"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}) {
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                textures.emplace_back();
                std::string path = "textures/cards/" + rank + "_" + suit + ".png";
                std::cout << path << std::endl;
                if(!textures.back().loadFromFile(path)) {
                    throw FileLoadFailure("Error: Failed to load card texture");
                }
                Card card(suit, rank, textures.back());
                cards.push_back(card);
                std::cout << "Texture address: " << &textures.back() << std::endl;
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
                sf::Texture texture;
                std::string path = "textures/cards/" + rank + "_" + suit + ".png";
                if(!texture.loadFromFile(path)) {
                    throw FileLoadFailure("Error: Failed to load card texture");
                }
                Card card(suit, rank, texture);
                cards.emplace_back(card);
            }
        }
        shuffleCards();
    }
