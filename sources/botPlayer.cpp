#include "../headers/botPlayer.h"

BotPlayer::BotPlayer() : Player(), sum(500) {}

BotPlayer::BotPlayer(const BotPlayer& other) : Player(other), sum(other.sum) {}

BotPlayer::~BotPlayer() {}

int BotPlayer::getSum() const {
    return sum;
}

void BotPlayer::subtractBet(int amount) {
    sum -= amount;
    if (sum < 0) {
        sum = 0;
    }
}

