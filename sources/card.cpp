#include <string>
#include <random>
#include <fstream>
#include "../headers/card.h"

//
    Card::Card(const std::string &suit, const std::string &rank) : suit(suit), rank(rank) {}

    Card::Card(const Card &other) : suit(other.suit), rank(other.rank) {}

    Card::~Card() {}

    std::string Card::getSuit() const {
            return suit;
    }

    std::string Card::getRank() const {
        return rank;
    }

    Card& Card::operator=(const Card &other) {
        suit = other.suit;
        rank = other.rank;
        return *this;
    }

    std::ostream& operator<<(std::ostream &os, const Card &card) {
    os << card.rank << " of " << card.suit << std::endl;
    return os;
    }