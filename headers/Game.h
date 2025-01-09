#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "TableCards.h"
#include <SFML/Graphics.hpp>
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include "DealerPlayer.h"
#include "BetStrategy.h"
#include "HumanBetStrategy.h"
#include "BotBetStrategy.h"
#include "Resources.h"

/**
 * @class Game
 * @brief The Game class encapsulates the logic, state, and graphical representation of a card game.
 */
class Game {
	static Game *game; ///< Singleton instance of the Game class
	Deck deck; ///< Deck object representing the game deck of cards
	std::vector<Player *> players; ///< Vector of pointers to Player objects participating in the game
	TableCards table; ///< TableCards object representing cards on the table
	int roundBet; ///< The current bet amount for the round
	sf::RenderWindow *window; ///< Pointer to the SFML RenderWindow for graphical output
	sf::Text player1Sum; ///< SFML Text object displaying Player 1's total score or balance
	sf::Text player2Sum; ///< SFML Text object displaying Player 2's total score or balance
	sf::Text textRoundBet; ///< SFML Text object displaying the current round's bet
	sf::Text textRoundPot; ///< SFML Text object displaying the current round's pot
	sf::Text promptText; ///< SFML Text object displaying input prompts to player 1
	std::string inputBet; ///< String to capture player 1's input for betting
	sf::Text inputText; ///< SFML Text object displaying the player 1's input
	sf::RectangleShape inputBox; ///< SFML RectangleShape representing the input box UI element
	std::vector<std::string> options; ///< List of available options for players
	std::vector<sf::Text> playerOptions; ///< SFML Text objects displaying player options
	sf::Font font; ///< SFML Font used for text rendering
	bool inputTextCompleted; ///< Tracks whether the input text entry has been completed
	bool botBet; ///< Flag to indicate if the bot has placed a bet
	bool humanBet; ///< Flag to indicate if the human player has placed a bet
	BetStrategy* betStrategy; ///< Pointer to the current betting strategy
	std::vector<sf::Sprite> cardSprites; ///< Vector of SFML sprites representing the cards
	Resources<sf::Texture> cardTextures; ///<Resources container for the card textures (uses a template)

	/**
	 * @brief Default Game constructor\n
	 * Constructs a new Game object and its components
	 **/
	Game();

public:
	/**
	 * @brief Returns the singleton instance of the Game class
	 * @return Pointer to the single Game instance
	 */
	static Game *getInstance();

	/**
	 * @brief Game copy constructor. Automatically disabled
	 * @param other Another Game-type object to assign from
	 */
	Game(const Game &other) = delete;

	/**
	 * @brief Game destructor
	 */
	~Game();

	/**
	 * @brief Copy assignment operator for the Game class. Automatically disabled
	 * @param other Another Game-type object to assign from
	 * @return Reference to the assigned Game object
	 */
	Game &operator=(const Game &other) = delete;

	/**
	 * @brief Gets the SFML Text object representing the player input
	 * @return The input text object
	 */
	sf::Text getInputText() const;

	/**
	 * @brief Provides access to the list of players in the game
	 * @return Reference to the vector of Player pointers
	 */
	std::vector<Player*> &getPlayers();

	/**
	 * @brief Gets the font used for rendering text
	 * @return The SFML Font object
	 */
	sf::Font getFont() const;

	/**
	 * @brief Checks if the bot has placed a bet
	 * @return True if the bot has bet; otherwise false
	 */
	bool getBotBet() const;

	/**
	 * @brief Sets the flag for a bot bet
	 * @param botBet_ True if the bot has placed a bet; otherwise false
	 */
	void setBotBet(bool botBet_);

	/**
	 * @brief Sets the flag for a human bet
	 * @param humanBet_ True if the human player has placed a bet; otherwise false
	 */
	void setHumanBet(bool humanBet_);

	/**
	 * @brief Sets the strategy to be used during the game
	 * @param strat Pointer to a BetStrategy object
	 */
	void setStrategy(BetStrategy* strat);

	/**
	 * @brief Executes the betting strategy for the game round
	 */
	void strategy();

	/**
	 * @brief Handles the player 1's text input for the bet
	 * @param event Reference to the game events
	 */
	void handleTextInput(sf::Event &event);

	/**
	 * @brief Draws the game interface and updates the window
	 */
	void drawGame();

	/**
	 * @brief Executes a single betting round
	 */
	void bettingRound();

	/**
	 * @brief Updates the displayed sums for all players
	 */
	void updateSums();

	/**
	 * @brief Resets the game state for a new round
	 */
	void resetRound();

	/**
	 * @brief Deals initial hands to all players
	 */
	void dealHands();

	/**
	 * @brief Displays the player 1's cards in the game window
	 */
	void displayHand();

	/**
	 * @brief Deals the "flop" round cards to the table
	 */
	void dealFlop();

	/**
	 * @brief Displays the "flop" round cards on the table
	 */
	void displayFlop();

	/**
	 * @brief Deals the "turn" and "river" round cards to the table
	 */
	void dealTurnRiver();

	/**
	 * @brief Displays the "turn" round cards on the table
	 */
	void displayTurn();

	/**
	 * @brief Displays the "river" round cards on the table
	 */
	void displayRiver();

	/**
	 * @brief Determines if a hand is a flush
	 * @param suitCount Vector of suit counts
	 * @return True if the hand is a flush, otherwise false
	 */
	static bool isFlush(const std::vector<int> &suitCount);

	/**
	 * @brief Determines if a hand is a straight
	 * @param rankCount Vector of rank counts
	 * @return True if the hand is a straight, otherwise false
	 */
	static bool isStraight(const std::vector<int> &rankCount);

	/**
	 * @brief Gets the maximum count of any rank in the hand
	 * @param rankCount Vector of rank counts
	 * @return The highest count of any rank
	 */
	static int getMaxCount(const std::vector<int> &rankCount);


	/**
	 * @brief Determines if a hand is a two pair
	 * @param rankCount Vector of rank counts
	 * @return True if the hand is a two pair, otherwise false
	 */
	static bool isTwoPair(const std::vector<int> &rankCount);

	/**
	 * @brief Gets the index of a rank in a predefined rank list
	 * @param rank The rank as a string
	 * @return The index of the rank
	 */
	static int getIndexRank(const std::string &rank);

	/**
	 * @brief Gets the index of a suit in a predefined suit list
	 * @param suit The suit as a string
	 * @return The index of the suit
	 */
	static int getIndexSuit(const std::string &suit);

	/**
	 * @brief Evaluates the high card score for a player's hand
	 * @param player The Player object whose hand is evaluated
	 * @return The score of the high card
	 */
	int highCardEvaluate(const Player &player);

	/**
	 * @brief Evaluates grouped cards in a player's hand
	 * @param player The Player object whose hand is evaluated
	 * @return The score of the grouped cards
	 */
	int cardGroupsEvaluate(const Player &player);

	/**
	 * @brief Overloads the << operator to output the game state
	 * @param os The output stream
	 * @param game The Game object to output
	 * @return The output stream with game state information
	 */
	friend std::ostream &operator<<(std::ostream &os, const Game &game);

	/**
	 * @brief Starts the game loop and handles game logic
	 */
	void play();
};

#endif //GAME_H
