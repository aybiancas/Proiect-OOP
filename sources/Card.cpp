#include <string>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/Card.h"
#include "../headers/FileLoadFailureExcept.h"


Card::Card() {
}

Card::Card(const std::string &suit, const std::string &rank) : suit(suit), rank(rank) {
	std::cout << "Creating card: " << rank << " of " << suit << std::endl;
}

Card::Card(const Card &other) : suit(other.suit), rank(other.rank), sprite(other.sprite) {
}

const std::string &Card::getSuit() const {
	return suit;
}

const std::string &Card::getRank() const {
	return rank;
}

Card &Card::operator=(const Card &other) {
	suit = other.suit;
	rank = other.rank;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
	os << card.rank << " of " << card.suit << std::endl;
	return os;
}

