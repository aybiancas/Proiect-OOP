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
	// std::string textureFile = "textures/cards/" + rank + "_" + suit + ".png";
	// std::cout << textureFile << std::endl;
	// if (!texture.loadFromFile(textureFile)) {
	// 	throw FileLoadFailure("Error: could not load card file!");
	// }
	// this->texture = texture;
	// sprite.setTexture(texture);
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
//
// const sf::Sprite &Card::getSprite() const {
// 	std::cout << "Returning sprite for " << rank << " of " << suit << std::endl;
// 	return sprite;
// }
//
// const sf::Texture &Card::getTexture() const {
// 	std::cout << "Returning texture for " << rank << " of " << suit << std::endl;
// 	return texture;
// }

