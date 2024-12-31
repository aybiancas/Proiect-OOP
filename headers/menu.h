
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"

/**
 * @class Menu
 * @brief The Menu class handles the user interface of the game, including displaying the menu, selecting options, and showing rules
 */
class Menu {
	static Menu* menu;
    sf::RenderWindow* window; ///< Pointer to the SFML render window
    sf::Font titleFont; ///< Font for the title of the menu
    sf::Font textFont; ///< Font for regular text (options) in the menu
    sf::Font ruleFont; ///< Font for the rules text in the menu
    sf::Texture bgImage; ///< Background texture for the menu
    sf::Text title; ///< Text object for the menu title
    sf::Text rulesText; ///< Text object for displaying rules in the menu
    std::vector<sf::Text> menuOptions; ///< List of text objects for the menu options
    std::vector<std::string> options; ///< List of menu option labels
    // Game* game; ///< Pointer to the Game object
    int selectedOption; ///< Index of the currently selected menu option
    int ruleShow; ///< Flag to determine if the rules should be shown

	/**
	 * @brief Default Menu constructor\n
	 * Initializes the menu, loading fonts, textures, and setting up default values
	 */
	Menu();

public:

	static Menu* getInstance();

	/**
	 * @brief Menu copy constructor
	 * @param other The Menu object to copy
	 */
    Menu(const Menu &other) = delete;

	/**
	 * @brief Menu destructor\n
	 * Cleans up any resources allocated by the menu
	 */
    ~Menu();

	/**
	 * @brief Assignment operator for the Menu class.
	 * @param other The Menu object to assign from.
	 * @return A reference to the current Menu object.
	 */
    Menu& operator=(const Menu &other) = delete;

    // void showMenu() const;

    // void selectOption(int choice);

	/**
	 * @brief Draws the menu to the screen\n
	 * Renders the title, menu options, and background image
	 */
    void drawMenu();

	/**
	 * @brief Draws the rules to the screen\n
	 * Displays the rules text in the menu if required
	 */
    void drawRules();

	/**
	 * @brief Runs the menu logic\n
	 * Handles user input for menu navigation and option selection
	 */
    void run();

	/**
	 * @brief Starts the game by initializing the game object\n
	 * Begins the game after the user selects the "Start" option
	 */
    void startGame();

    // static void showRules();

	/**
	 * @brief Overloaded output stream operator to print the menu details
	 * @param os The output stream to write to
	 * @param menu The Menu object to output
	 * @return The output stream with the menu information
	 */
    friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
};

#endif //MENU_H
