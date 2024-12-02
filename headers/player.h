
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"

class Player {
    std::vector<Card> cards;

public:

    ///Player constructor
    Player();

    ///Player copy constructor
    Player(const Player &other);

    ///Player destructor
    virtual ~Player();

    ///Player cards getter
    [[nodiscard]] const std::vector<Card>& getPlayerCards() const;

    ///Overloaded = operator
    Player& operator=(const Player &other);

    ///Adds a card object into the Player cards vector
    void addCard(const Card& card);

    void clearHand();


    ///Overloaded << operator
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif //PLAYER_H
