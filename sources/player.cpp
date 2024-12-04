
#include "../headers/player.h"
#include "../headers/card.h"
#include <iostream>

    ///Player constructor.\n\n
    ///Called every time a Player object is created.
    Player::Player() {
        std::cout << "Player constructor" << std::endl;
    }

///Player copy constructor
Player::Player(const Player &other) : cards(other.cards) {}

///Player destructor.\n\n
///Called every time a Player object is destroyed (when the program ends)
Player::~Player() {
        std::cout << "Player destructor" << std::endl;
    }

///Player cards getter.\n\n
///Used in other classes to access the Player cards for subsequent operations.
const std::vector<Card>& Player::getPlayerCards() const {
        return cards;
    }

///Overloaded = operator
Player& Player::operator=(const Player &other) {
        cards = other.cards;
        return *this;
    }

///Adds a card object into the Player card vector.\n\n
///Used to give the players the amount of cards needed for the game.
void Player::addCard(const Card& card) {
        cards.push_back(card);
    }

void Player::clearHand() {
        cards.clear();
    }

///Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
        for (const auto &card : player.cards) {
            os << card << std::endl;
        }
        return os;
    }
