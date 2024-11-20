
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <iostream>

class Deck {
    std::vector<Card> cards;
    std::vector<std::string> suits;
    std::vector<std::string> ranks;

public:
    Deck();

    Deck(const Deck &other);

    ~Deck();

    Deck& operator=(const Deck &other);

    void shuffleCards();

    friend std::ostream& operator<<(std::ostream &os, const Deck &deck);

    Card dealCard ();
};

#endif //DECK_H
