
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"

/**
 * @class Player
 * @brief Represents a player in a card game
 */
class Player {
    std::vector<Card> cards; ///< The player's hand of cards

public:

	/**
	 * @brief Default Player constructor\n
	 */
    Player();

	/**
	 * @brief Player Copy constructor
	 * @param other The Player object to copy
	 */
    Player(const Player &other);

	/**
	 * @brief Player Destructor
	 */
    virtual ~Player();

	/**
	 * @brief Retrieves the cards in the player's hand
	 * @return A constant reference to a vector of Cards
	 */
    [[nodiscard]] const std::vector<Card>& getPlayerCards() const;

	/**
	 * @brief Assignment operator for Player
	 * @param other The Player object to assign from
	 * @return A reference to this Player object
	 */
    Player& operator=(const Player &other);

	/**
	 * @brief Adds a card to the player's hand
	 * @param card The card to be added
	 */
    void addCard(const Card& card);

	/**
	 * @brief Clears all cards from the player's hand
	 */
    void clearHand();

	/**
	 * @brief Adds a specified amount to the player's score\n\n
	 * This function is pure virtual and is implemented in derived classes
	 * @param amount The amount to add to the player's score
	 */
    virtual void addSum(int amount) = 0;

	/**
	 * @brief Stream insertion operator for Player
	 * @param os The output stream to which the player's information will be written.
	 * @param player The Player object to be written to the stream.
	 * @return A reference to the output stream.
	 */
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

	/**
	 * @brief Retrieves the current score of the player\n
	 * This function is pure virtual and is implemented in derived classes
	 * @return The player's score
	 */
    virtual int getSum() = 0;

	/**
	 * @brief Retrieves the player's current pot value
	 * @return The game pot that is kept by the dealer player
	 */
    virtual int getPot() = 0;

	/**
	 * @brief Subtracts the bet amount from the player's sum\n
	 * This function is pure virtual and is implemented in derived classes
	 * @param amount The amount to subtract from the player's score
	 */
    virtual void subtractBet(int amount) = 0;

	virtual void setSum(int amount) = 0;

};

#endif //PLAYER_H