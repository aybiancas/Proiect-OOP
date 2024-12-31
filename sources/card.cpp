#include <string>
#include <random>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../headers/card.h"
#include "../headers/FileLoadFailureExcept.h"


    Card::Card() {}

    Card::Card(const std::string &suit, const std::string &rank, const sf::Texture &texture) : suit(suit), rank(rank) {
        sprite.setTexture(texture);
    }

    Card::Card(const Card &other) : suit(other.suit), rank(other.rank) {}

    const std::string& Card::getSuit() const {
            return suit;
    }

    const std::string& Card::getRank() const {
        return rank;
    }

    Card& Card::operator=(const Card &other) {
        suit = other.suit;
        rank = other.rank;
        return *this;
    }

    std::ostream& operator<<(std::ostream &os, const Card &card) {
    os << card.rank << " of " << card.suit << std::endl;
    return os;
    }

    const sf::Sprite &Card::getSprite() const {
        return sprite;
    }

    void Card::setSprite(const sf::Sprite& _sprite) {
        this->sprite = _sprite;
    }

    void Card::loadTexture(const std::string &path) {
        if (!texture.loadFromFile(path)) {
            throw FileLoadFailure("Error: Failed to load card texture");
        }
        sprite.setTexture(texture);
    }