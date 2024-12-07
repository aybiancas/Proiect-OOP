
#ifndef TABLECARDS_H
#define TABLECARDS_H

#include <iostream>
#include <vector>
#include "card.h"


class TableCards {
    std::vector<Card> cards;

public:
    // constructor
    TableCards();

    // constructor de copiere
    TableCards(const TableCards &other);

    // destructor
    ~TableCards();

    [[nodiscard]] const std::vector<Card>& getTableCards() const;

    // operator =
    TableCards& operator=(const TableCards &other);

    // adauga cartea in vectorul de carti de pe masa
    void addCard(const Card& card);

    void clearTable();

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const TableCards& table);
};

#endif //TABLECARDS_H
