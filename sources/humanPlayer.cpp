#include "../headers/humanPlayer.h"

HumanPlayer::HumanPlayer() : Player(), sum(1000) {}

HumanPlayer::HumanPlayer(const HumanPlayer &other) : Player(other), sum(other.sum) {}

HumanPlayer::~HumanPlayer() {}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer &other) {
    Player::operator=(other);
    sum = other.sum;
    return *this;
}

int HumanPlayer::getSum() {
    return sum;
}

void HumanPlayer::subtractBet(int amount) {
    sum -= amount;
    if (sum < 0) {
        sum = 0;
    }
}

void HumanPlayer::addSum(int amount) {
    sum += amount;
}

int HumanPlayer::getPot() {
    return 0;
}

void HumanPlayer::addPot(int amount) {}

