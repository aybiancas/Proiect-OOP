#include "../headers/botPlayer.h"

    BotPlayer::BotPlayer() : Player(), sum(1000) {}

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

    void BotPlayer::addSum(int amount) {
        sum += amount;
    }

