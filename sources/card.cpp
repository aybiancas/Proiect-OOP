#include <string>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/card.h"
#include "../headers/FileLoadFailureExcept.h"


Card::Card() {
}

Card::Card(const std::string &suit, const std::string &rank, const sf::Texture &texture) : suit(suit), rank(rank) {
	std::cout << "Creating card: " << rank << " of " << suit << std::endl;
	this->texture = texture;
	sprite.setTexture(texture);
	// if (texture.getSize().x == 0 || texture.getSize().y == 0) {
	//     std::cout << "Error: Texture is empty or failed to load!" << std::endl;
	// }
	if (sprite.getTexture() == nullptr) {
		std::cout << "Error: Sprite texture is not set!" << std::endl;
	} else {
		std::cout << "Sprite texture set successfully!" << std::endl;
	}
	std::cout << "Texture address: " << &this->texture << std::endl;
	std::cout << "Sprite address: " << &sprite << std::endl;
}

Card::Card(const Card &other) : suit(other.suit), rank(other.rank), sprite(other.sprite) {
	std::cout << "Copied sprite texture address: " << sprite.getTexture() << std::endl;
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

const sf::Sprite &Card::getSprite() const {
	std::cout << "Returning sprite for " << rank << " of " << suit << std::endl;
	return sprite;
}

const sf::Texture &Card::getTexture() const {
	std::cout << "Returning texture for " << rank << " of " << suit << std::endl;
	return texture;
}

