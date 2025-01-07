
#ifndef BOTPLAYER_H
#define BOTPLAYER_H
#include "Player.h"

/**
 * @brief Represents a bot player in a card game\n
 * This class extends the Player class and defines behaviors specific to a bot player
 */
class BotPlayer : public Player {
    int sum; ///< The bot player's current sum

public:

	/**
	 * @brief Default BotPlayer constructor
	 */
    BotPlayer();

	/**
	 * @brief BotPlayer Copy constructor
	 * @param other The BotPlayer object to copy.
	 */
    BotPlayer(const BotPlayer& other);

	/**
	 * @brief BotPlayer Destructor
	 */
    ~BotPlayer() override;

	/**
	 * @brief Assignment operator for BotPlayer
	 * @param other The BotPlayer object to assign from
	 * @return A reference to this BotPlayer object
	 */
    BotPlayer& operator=(const BotPlayer &other);

	/**
	 * @brief Retrieves the current score of the bot player
	 * @return The bot player's score
	 */
    int getSum() override;

	/**
	 * @brief Subtracts the bet amount from the bot player's sum
	 * @param amount The amount to subtract from the sum
	 */
    void subtractBet(int amount) override;

	/**
	* @brief Adds a specified amount to the bot player's sum
	* @param amount The amount to add to the sum
	*/
    void addSum(int amount) override;

    int getPot() override;

	void setSum(int amount) override;

    // void addPot(int amount) override;

};

#endif //BOTPLAYER_H