
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class HumanPlayer : public Player {
    int sum;

    public:

    HumanPlayer();

    HumanPlayer(const HumanPlayer &other);

    ~HumanPlayer() override;



};

#endif //HUMANPLAYER_H
