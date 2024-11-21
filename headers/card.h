
#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
    std::string suit;
    std::string rank;

public:
    Card(const std::string &suit, const std::string &rank);

    Card(const Card &other);

    ~Card();

    [[nodiscard]] const std::string& getSuit() const;

    [[nodiscard]] const std::string& getRank() const;

    Card& operator=(const Card &other);

    friend std::ostream& operator<<(std::ostream &os, const Card &card);
};

#endif //CARD_H
