
#ifndef CARD_H
#define CARD_H

#include <string>
#include <SFML/Graphics.hpp>

/**
 * @class Card
 * @brief Represents a playing card with a suit, rank, and sprite for graphical representation
 */
class Card {
    std::string suit; ///< The suit of the card
    std::string rank; ///< The rank of the card
    sf::Sprite sprite; ///< The graphical representation of the card

public:
	/**
	 * @brief Default Card constructor
	 */
    Card();

	/**
	 * @brief Parameterized constructor that initializes a card with the specified suit and rank.
	 *
	 * @param suit The suit of the card
	 * @param rank The rank of the card
	 */
    Card(const std::string &suit, const std::string &rank);

	/**
	 * @brief Card Copy constructor
	 *
	 * @param other The card to copy.
	 */
    Card(const Card &other);

	/**
	 * @brief Default Card destructor
	 */
    ~Card() = default;

	/**
	 * @brief Gets the suit of the card
	 *
	 * @return A constant reference to the suit of the card
	 */
    [[nodiscard]] const std::string& getSuit() const;

	/**
	 * @brief Gets the rank of the card
	 *
	 * @return A constant reference to the rank of the card
	 */
    [[nodiscard]] const std::string& getRank() const;

	/**
	 * @brief Copy assignment operator for the Card class
	 *
	 * @param other The card to copy
	 * @return A reference to the current card
	 */
    Card& operator=(const Card &other);

	/**
	 * @brief Stream insertion operator to output the card's suit and rank to an output stream.
	 *
	 * @param os The output stream.
	 * @param card The card to output.
	 * @return The output stream with the card's details.
	 */
    friend std::ostream& operator<<(std::ostream &os, const Card &card);

	/**
	 * @brief Gets the sprite associated with the card
	 *
	 * @return A constant reference to the sprite representing the card
	 */
    const sf::Sprite &getSprite() const;

	/**
	 * @brief Sets the sprite for the card
	 *
	 * @param sprite The new sprite for the card
	 */
    void setSprite(const sf::Sprite &sprite);
};

#endif //CARD_H
