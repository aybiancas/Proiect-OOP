#include "../headers/DealerPlayer.h"

DealerPlayer::DealerPlayer() :
    Player(),
    pot(0) {}

DealerPlayer::DealerPlayer(const DealerPlayer &other) :
    Player(other),
    pot(other.pot) {}

DealerPlayer::~DealerPlayer() {}

DealerPlayer& DealerPlayer::operator=(const DealerPlayer &other) {
    Player::operator=(other);
    // deck = other.deck;
    pot = other.pot;
    return *this;
}

int DealerPlayer::getPot() {
    return pot;
}


void DealerPlayer::addSum(int amount) {
    pot += amount;
}

int DealerPlayer::getSum() {
    return 0;
}

void DealerPlayer::subtractBet(int amount) {
    pot -= amount;
}

void DealerPlayer::setSum(int amount) {
    this->pot = amount;
}

// Card DealerPlayer::dealCard() {}


