#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @class Deck
 * @brief Represents a deck of playing cards
 */
class Deck {
	std::vector<Card> cards; ///< A vector containing the cards in the deck
	std::vector<std::string> suits; ///< A vector containing the suit names
	std::vector<std::string> ranks; ///< A vector containing the rank names

public:
	/**
	 * @brief Default Deck constructor that initializes a deck with 52 cards
	 */
	Deck();

	/**
	 * @brief Deck copy constructor to create a new deck as a copy of another
	 * @param other The deck to copy from
	 */
	Deck(const Deck &other);

	/**
	 * @brief Deck destructor
	 */
	~Deck();

	/**
	 * @brief Assignment operator to assign one deck to another
	 * @param other The deck to copy from
	 * @return A reference to the assigned deck
	 */
	Deck& operator=(const Deck &other);

	/**
	 * @brief Shuffles the cards in the deck\n
	 * Randomly reorders the cards to ensure a fair distribution
	 */
	void shuffleCards();

	/**
	 * @brief Stream insertion operator for printing the deck to an output stream
	 * @param os The output stream to print to
	 * @param deck The deck object to print
	 * @return The modified output stream
	 */
	friend std::ostream& operator<<(std::ostream &os, const Deck &deck);

	/**
	 * @brief Deals a single card from the deck\n
	 * Removes the last card from the deck and returns it
	 * @return The dealt card
	 */
	Card dealCard();

	/**
	 * @brief Resets the deck to its original state with 52 cards\n
	 * This function recreates the deck with all 52 cards, shuffling them
	 */
	void resetDeck();

	/**
	 * @brief Retrieves all of the possible card suits
	 * @return The string vector of suits
	 */
	[[nodiscard]] const std::vector<std::string> &getSuits() const;

	/**
	 * @brief Retrieves all of the possible card ranks
	 * @return The string vector of ranks
	 */
	[[nodiscard]] const std::vector<std::string> &getRanks() const;
};

#endif //DECK_H