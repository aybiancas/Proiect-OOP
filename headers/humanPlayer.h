
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

    HumanPlayer& operator=(const HumanPlayer &other);

    int getSum() const;

    void subtractBet(int amount);

    void addSum(int amount) override;

};

#endif //HUMANPLAYER_H