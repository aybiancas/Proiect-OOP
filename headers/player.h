
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"

class Player {
    std::vector<Card> cards;

public:

    Player();

    Player(const Player &other);

    virtual ~Player();

    [[nodiscard]] const std::vector<Card>& getPlayerCards() const;

    Player& operator=(const Player &other);

    void addCard(const Card& card);

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif //PLAYER_H
