#include "../headers/menu.h"
#include "../headers/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

    Menu::Menu() :
    window(nullptr),
    options({"Start", "Reguli", "Iesi"}),
    game(nullptr),
    selectedOption(0),
    ruleShow(0) {

        std::cout << "Meniu creat." << std::endl;

        window = new sf::RenderWindow(sf::VideoMode(1300, 900), "Texas Hold' em");
        window->setFramerateLimit(20);

        if (!titleFont.loadFromFile("fonts/Bleeding_Cowboys.ttf")) {
            std::cout << "Eroare: nu s-a incarcat fontul." << std::endl;
        }

        if (!textFont.loadFromFile("fonts/BroncoPersonalUse.ttf")) {
            std::cout << "Eroare: nu s-a incarcat fontul." << std::endl;
        }

        if (!ruleFont.loadFromFile("fonts/BabelSans.ttf")) {
            std::cout << "Eroare: nu s-a incarcat fontul." << std::endl;
        }


        title.setFont(titleFont);
        title.setString("Texas Hold' em");
        title.setCharacterSize(100);
        title.setFillColor(sf::Color::White);
        title.setPosition(650 - title.getGlobalBounds().width / 2, 150);

        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text optionText;
            optionText.setFont(textFont);
            optionText.setString(options[i]);
            optionText.setCharacterSize(50);
            optionText.setPosition(650 - optionText.getGlobalBounds().width / 2, 350 + i * 150);
            menuOptions.push_back(optionText);
        }

        rulesText.setFont(ruleFont);
        rulesText.setCharacterSize(15);
        rulesText.setFillColor(sf::Color::White);
        rulesText.setPosition(50, 150);
    }

    Menu::Menu (const Menu &other) : options(other.options), game(other.game), selectedOption(other.selectedOption) {}

    Menu::~Menu() {
        delete game;
        delete window;
        std::cout << "Meniu inchis." << std::endl;
    }

    Menu& Menu::operator=(const Menu &other) {
        options = other.options;
        game = other.game;
        selectedOption = other.selectedOption;
        return *this;
    }


    // optiuni de meniu
    void Menu::showMenu() const {
        std::cout << "Texas Hold' em" << std::endl;
        for(int i = 0; i < 3; i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
    }

    // // alegerea optiunii de meniu
    // void Menu::selectOption(int choice) {
    //     std::cout << "Optiune: ";
    //
    //     switch (choice) {
    //         case 1:
    //             std::cout << "Incepe jocul ..." << std::endl;
    //         startGame();
    //         // apelare functie de joc
    //         break;
    //
    //         case 2:
    //             std::cout << "Reguli: [...]" << std::endl;
    //         showRules();
    //         // idee: sa ramana in meniu inainte de a inchide meniul
    //         break;
    //
    //         case 3:
    //             std::cout << "Se inchide ..." << std::endl;
    //         // opreste programul
    //         break;
    //
    //         default:
    //             std::cout << "Invalid ..." << std::endl;
    //     }
    // }


    void Menu::drawMenu() {
        window->clear(sf::Color::Black);
        window->draw(title);

        for (size_t i = 0; i < menuOptions.size(); ++i) {
            if (i == selectedOption) {
                menuOptions[i].setFillColor(sf::Color::Red);
            } else {
                menuOptions[i].setFillColor(sf::Color::White);
            }
            window->draw(menuOptions[i]);
        }

        window->display();
    }

    void Menu::drawRules() {

        sf::Text backText;

        window->clear(sf::Color::Black);
        window->draw(rulesText);

        backText.setFont(textFont);
        backText.setString("< Meniu (ESC)");
        backText.setCharacterSize(40);
        backText.setPosition(40, 40);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (backText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            backText.setFillColor(sf::Color::Red);
        }
        else {
            backText.setFillColor(sf::Color::White);
        }

        window->draw(backText);
        window->display();
    }

    void Menu::run () {
        std::ifstream f("rules.txt");
        std::string line, rules;
        while (std::getline(f, line)) {
            rules += line + "\n";
        }
        f.close();
        rulesText.setString(rules);
        rulesText.setCharacterSize(25);

        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if (!ruleShow) {
                    if (event.type == sf::Event::MouseMoved) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                        selectedOption = -1;
                        for (size_t i = 0; i < menuOptions.size(); ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                selectedOption = i;
                                break;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (selectedOption == 0) {
                            startGame();
                        }
                        else if (selectedOption == 1) {
                            ruleShow = true;
                        }
                        else if (selectedOption == 2) {
                            window->close();
                        }
                    }
                }
                else {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        ruleShow = false;
                    }
                }
            }
            if (ruleShow) {
                drawRules();
            }
            else {
                drawMenu();
            }
        }
    }

    void Menu::startGame() {
        if (game != nullptr) {
            delete game;
        }
        game = new Game();
        window->close();
        game->play();
    }

    // void Menu::showRules () {
    //     // citeste fisierul de reguli si le afiseaza pe ecran
    //     std::ifstream f("../rules.txt");
    //     std::string line;
    //     while (std::getline(f, line)) {
    //         std::cout << line << std::endl;
    //     }
    //     f.close();
    //     std::cout << std::endl;
    // }

    // operator cout
    std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        for (int i = 0; i < 3; i++) {
            os << i + 1 << ". " << menu.options[i] << std::endl;
        }
        return os;
    }