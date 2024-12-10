
#include "../headers/player.h"
#include "../headers/card.h"
#include <iostream>

    Player::Player() {
        std::cout << "Player constructor" << std::endl;
    }

    Player::Player(const Player &other) : cards(other.cards) {}

    Player::~Player() {
            std::cout << "Player destructor" << std::endl;
        }

    const std::vector<Card>& Player::getPlayerCards() const {
            return cards;
        }

    Player& Player::operator=(const Player &other) {
            cards = other.cards;
            return *this;
        }

    void Player::addCard(const Card& card) {
            cards.push_back(card);
        }

    void Player::clearHand() {
            cards.clear();
        }

    std::ostream& operator<<(std::ostream& os, const Player& player) {
            for (const auto &card : player.cards) {
                os << card << std::endl;
            }
            return os;
        }

    // int Player::getPot() {}

    void Player::addPot(int amount) {}

    void Player::subtractBet(int amount) {}

