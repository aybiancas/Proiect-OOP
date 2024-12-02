
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class HumanPlayer : public Player {
    int sum;

    public:

    ///HumanPlayer constructor
    HumanPlayer();

    ///HumanPlayer copy constructor
    HumanPlayer(const HumanPlayer &other);

    ///HumanPlayer destructor
    ~HumanPlayer() override;

    int getSum() const;

    void subtractBet(int amount);


};

#endif //HUMANPLAYER_H
