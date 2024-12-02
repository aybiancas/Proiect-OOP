
#ifndef BOTPLAYER_H
#define BOTPLAYER_H
#include "player.h"

class BotPlayer : public Player {
    int sum;

    public:

    BotPlayer();

    BotPlayer(const BotPlayer& other);

    ~BotPlayer() override;

    int getSum() const;

    void subtractBet(int amount);

    void addSum(int amount) override;

};

#endif //BOTPLAYER_H
