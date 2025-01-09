
#ifndef DEALERPLAYER_H
#define DEALERPLAYER_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"

/**
 * @brief Represents a dealer player in a card game
 * This class extends the Player class and defines behaviors specific to a dealer player
 */
class DealerPlayer : public Player {
    int pot; ///< The game pot that is currently kept by the dealer player

public:
	/**
	 * @brief Default DealerPlayer constructor
	 */
    DealerPlayer();

	/**
	 * @brief DealerPlayer Copy constructor
	 * @param other The DealerPlayer object to copy
	 */
    DealerPlayer(const DealerPlayer &other);

	/**
	 * @brief DealerPlayer Destructor
	 */
    ~DealerPlayer() override;

	/**
	 * @brief Assignment operator for DealerPlayer
	 * @param other The DealerPlayer object to assign from
	 * @return A reference to this DealerPlayer object
	 */
    DealerPlayer& operator=(const DealerPlayer &other);

	/**
	 * @brief Retrieves the current pot value
	 * @return The pot value that the dealer stores
	 */
    int getPot() override;

	/**
	 * @brief Adds a certain amount to the player's sum
	 * @param amount The amount to add to the sum
	 */
	void addSum(int amount) override;

	/**
	 * @brief Retrieves the player's sum
	 * @return The sum value of the player
	 */
	int getSum() override;

	/**
	 * @brief Subtracts a certain amount from the player's sum
	 * @param amount The amount to subtract from the sum
	 */
	void subtractBet(int amount) override;

	/**
	 * @brief Sets the player sum to a certain value
	 * @param amount the value to set the sum to
	 */
	void setSum(int amount) override;
};

#endif //DEALERPLAYER_H