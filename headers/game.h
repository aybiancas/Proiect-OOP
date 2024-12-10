#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "tableCards.h"
#include "humanPlayer.h"
#include <SFML/Graphics.hpp>
#include "botPlayer.h"
#include "dealerPlayer.h"

/**
 * @class Game
 * @brief Represents the main game logic for the Texas Hold' em game
 */
class Game {
    Deck deck; ///< Deck object representing the game deck of cards
    // HumanPlayer player1;
    // BotPlayer player2;
    // DealerPlayer dealer;
    // std::vector<std::unique_ptr<Player>> players;
    std::vector<Player *> players; ///< Vector of pointers to Player objects participating in the game
    TableCards table; ///< TableCards object representing cards on the table
    int roundBet; ///< The current bet amount for the round
    // std::vector<std::string> handTypes; ///< List of possible hand types in the game
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
    bool botBet;
    bool humanBet;


public:
    /**
     * @brief Default Game constructor\n
     * Constructs a new Game object and its components
     **/
    Game();

    /**
     * @brief Game copy constructor
     * @param other Another Game-type object to assign from
     */
    Game(const Game &other);

    /**
     * @brief Game destructor
     */
    ~Game();

    /**
     * @brief Copy assignment operator for the Game class
     * @param other Another Game-type object to assign from
     * @return Reference to the assigned Game object
     */
    Game &operator=(const Game &other);


    /**
     * @brief Handles the player 1's text input for the bet
     */
    void handleTextInput();

    /**
     * @brief Draws the game interface and updates the window
     */
    void drawGame();

    /**
     * @brief Handles the betting logic for the human player
     */
    void bettingHuman();

    /**
     * @brief Handles the betting logic for the bot player.
     */
    void bettingBot();

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
