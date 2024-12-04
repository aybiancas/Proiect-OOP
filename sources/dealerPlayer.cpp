#include "../headers/dealerPlayer.h"

DealerPlayer::DealerPlayer() :
    Player(),
    pot(0) {}

DealerPlayer::DealerPlayer(const DealerPlayer &other) :
    Player(other),
    pot(other.pot) {}

DealerPlayer::~DealerPlayer() {}

DealerPlayer& DealerPlayer::operator=(const DealerPlayer &other) {
    Player::operator=(other);
    deck = other.deck;
    pot = other.pot;
    return *this;
}

int DealerPlayer::getPot() const {
    return pot;
}

void DealerPlayer::addPot(int amount) {
    pot += amount;
}

void DealerPlayer::addSum(int amount) {
    pot += amount;
}