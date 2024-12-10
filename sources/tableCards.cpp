#include "../headers/tableCards.h"
#include "../headers/card.h"
#include <iostream>
#include <vector>

    TableCards::TableCards() {
        std::cout << "Masa constructor" << std::endl;
    }

    TableCards::TableCards(const TableCards &other) : cards(other.cards) {}

    TableCards::~TableCards() {
        std::cout << "Masa destructor" << std::endl;
    }

    const std::vector<Card>& TableCards::getTableCards() const {
        return cards;
    }

    TableCards& TableCards::operator=(const TableCards &other) {
        cards = other.cards;
        return *this;
    }

    void TableCards::addCard(const Card& card) {
        cards.push_back(card);
    }

    void TableCards::clearTable() {
        cards.clear();
    }

    std::ostream& operator<<(std::ostream& os, const TableCards& table) {
        os << "Carti pe masa: " << std::endl;
        for (const auto &card : table.cards) {
            os << card << std::endl;
        }
        return os;
    }
