#include "../headers/tableCards.h"
#include "../headers/card.h"
#include <iostream>
#include <vector>

    // constructor
    TableCards::TableCards() {
        std::cout << "Masa constructor" << std::endl;
    }

    // constructor de copiere
    TableCards::TableCards(const TableCards &other) : cards(other.cards) {}

    // destructor
    TableCards::~TableCards() {
        std::cout << "Masa destructor" << std::endl;
    }

    const std::vector<Card>& TableCards::getTableCards() const {
        return cards;
    }

    // operator =
    TableCards& TableCards::operator=(const TableCards &other) {
        cards = other.cards;
        return *this;
    }

    // adauga cartea in vectorul de carti de pe masa
    void TableCards::addCard(const Card& card) {
        cards.push_back(card);
    }

    // adauga suma la roundBet pt bet ul unei runde
    // void TableCards::bet(int amount) {
    //     sum = sum - amount;
    // }

    // in cazul castigului rundei se adauga suma totala din bet ul rundei in suma playerului castigator
    // void TableCards::win(int amount) {
    //     sum = sum + amount;
    // }

    // void TableCards::fold() {
    //     folded = 1;
    // }

    // void TableCards::resetHand() {
    //     cards.clear();
    //     folded = 0;
    // }


    // operator cout
    std::ostream& operator<<(std::ostream& os, const TableCards& table) {
        os << "Carti pe masa: " << std::endl;
        for (const auto &card : table.cards) {
            os << card << std::endl;
        }
        return os;
    }
