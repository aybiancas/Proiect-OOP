
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

/**
 * @brief Represents a human player in a card game
 *
 * This class extends the Player class and defines behaviors specific to a human player
 */
class HumanPlayer : public Player {
    int sum; ///< The human player's current sum

public:

	/**
	 * @brief Default HumanPlayer constructor
	 */
    HumanPlayer();

	/**
	 * @brief HumanPlayer Copy constructor
	 * @param other The HumanPlayer object to copy.
	 */
    HumanPlayer(const HumanPlayer &other);

	/**
	 * @brief HumanPlayer Destructor
	 */
    ~HumanPlayer() override;

	/**
	 * @brief Assignment operator for HumanPlayer
	 * @param other The HumanPlayer object to assign from
	 * @return A reference to this HumanPlayer object
	 */
    HumanPlayer& operator=(const HumanPlayer &other);

	/**
	 * @brief Retrieves the current sum of the human player
	 * @return The human player's sum
	 */
    int getSum() override;

	/**
	 * @brief Subtracts the bet amount from the human player's sum
	 * @param amount The amount to subtract from the sum
	 */
    void subtractBet(int amount) override;

	/**
	 * @brief Adds the pot amount to the human player's sum
	 * @param amount The amount to add to the sum
	 */
    void addSum(int amount) override;

    // void addPot(int amount) override;

    int getPot() override;

	void setSum(int amount) override;

};

#endif //HUMANPLAYER_H