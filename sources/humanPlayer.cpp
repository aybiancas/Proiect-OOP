#include "../headers/humanPlayer.h"

    HumanPlayer::HumanPlayer() : Player(), sum(500) {}

    HumanPlayer::HumanPlayer(const HumanPlayer &other) : Player(other), sum(other.sum) {}

    HumanPlayer::~HumanPlayer() {}

    int HumanPlayer::getSum() const {
        return sum;
    }

    void HumanPlayer::subtractBet(int amount) {
        sum -= amount;
        if (sum < 0) {
            sum = 0;
        }
    }





