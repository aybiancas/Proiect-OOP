#include "../headers/dealerPlayer.h"

DealerPlayer::DealerPlayer() :
    Player(),
    pot(0) {

}

DealerPlayer::DealerPlayer(const DealerPlayer &other) :
    Player(other),
    pot(other.pot) {

}

DealerPlayer::~DealerPlayer() {

}

int DealerPlayer::getPot() const {
    return pot;
}

void DealerPlayer::addPot(int amount) {
    pot += amount;
}

