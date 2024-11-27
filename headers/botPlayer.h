
#ifndef BOTPLAYER_H
#define BOTPLAYER_H
#include "player.h"

class BotPlayer : public Player {
    int sum;

    public:

    BotPlayer();

    BotPlayer(const BotPlayer& other);

    virtual ~BotPlayer();
};

#endif //BOTPLAYER_H
