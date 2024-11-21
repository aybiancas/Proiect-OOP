#include "../headers/player.h"
#include "../headers/card.h"
#include <iostream>

    Player::Player() : sum(500) {
        std::cout << "Player constructor" << std::endl;
    }

    Player::Player(const Player &other) : cards(other.cards), sum(other.sum) {}

    Player::~Player() {
        std::cout << "Player destructor" << std::endl;
    }

    const std::vector<Card>& Player::getPlayerCards() const {
        return cards;
    }

    Player& Player::operator=(const Player &other) {
        cards = other.cards;
        sum = other.sum;
        return *this;
    }

    void Player::addCard(const Card& card) {
        cards.push_back(card);
    }

    std::ostream& operator<<(std::ostream& os, const Player& player) {
        for (const auto &card : player.cards) {
            os << card << std::endl;
        }
        return os;
    }
