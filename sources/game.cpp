#include <iostream>
#include <random>
#include <vector>
#include "../headers/card.h"
#include "../headers/deck.h"
#include "../headers/player.h"
#include "../headers/tableCards.h"
#include "../headers/game.h"
#include "../headers/BetInputInvalidExcept.h"
#include "../headers/FileLoadFailureExcept.h"
#include "../headers/NotEnoughFundsExcept.h"

    Game::Game() :
    deck(),
    roundBet(0),
    window(nullptr),
    botBet(true),
    humanBet(true) {
        std::cout << "Game constructor" << std::endl;
        deck.shuffleCards();
        deck.shuffleCards();
        // deck.shuffleCards();
        // deck.shuffleCards();
        // deck.shuffleCards();

        players.push_back(new HumanPlayer);
        players.push_back(new BotPlayer);
        players.push_back(new DealerPlayer);

        window = new sf::RenderWindow(sf::VideoMode(1300, 900), "");
        window->setFramerateLimit(20);

        if (!font.loadFromFile("fonts/BroncoPersonalUse.ttf")) {
            throw FileLoadFailure("Error: Failed to load fonts");
        }

        player1Sum.setFont(font);
        player1Sum.setString("Suma P1: " + std::to_string(players[0]->getSum()));
        std::cout << players[0]->getSum();
        player1Sum.setCharacterSize(40);
        player1Sum.setFillColor(sf::Color::White);
        player1Sum.setPosition(650 - player1Sum.getGlobalBounds().width / 2, 800);

        player2Sum.setFont(font);
        player2Sum.setString("Suma P2: " + std::to_string(players[1]->getSum()));
        std::cout << players[1]->getSum();
        player2Sum.setCharacterSize(40);
        player2Sum.setFillColor(sf::Color::White);
        player2Sum.setPosition(650 - player1Sum.getGlobalBounds().width / 2, 50);

        textRoundPot.setFont(font);
        textRoundPot.setString("Pot: " + std::to_string(players[2]->getPot()));
        std::cout << players[2]->getPot();
        textRoundPot.setCharacterSize(40);
        textRoundPot.setFillColor(sf::Color::White);
        textRoundPot.setPosition(350 - textRoundPot.getGlobalBounds().width / 2, 250);

        textRoundBet.setFont(font);
        textRoundBet.setString("Pariu curent: " + std::to_string(roundBet));
        std::cout << roundBet;
        textRoundBet.setCharacterSize(40);
        textRoundBet.setFillColor(sf::Color::White);
        textRoundBet.setPosition(650 - textRoundBet.getGlobalBounds().width / 2, 150);

        promptText.setFont(font);
        promptText.setString("Introdu o suma: ");
        promptText.setCharacterSize(40);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition(300, 460);

        inputBox.setSize(sf::Vector2f(200, 50));
        inputBox.setFillColor(sf::Color::Black);
        inputBox.setPosition(650, 460);

        inputText.setFont(font);
        inputText.setString(inputBet);
        inputText.setCharacterSize(30);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(650, 300);

    }

    // constructor de copiere
    Game::Game(const Game &other) :
    deck(other.deck),
    // player1(other.player1),
    // player2(other.player2),
    // dealer(other.dealer),
    roundBet(other.roundBet),
    window(other.window),
    botBet(other.botBet),
    humanBet(other.humanBet) {}

    // destructor
    Game::~Game() {
        std::cout << "Game destructor" << std::endl;
    }

    // operator =
    Game& Game::operator=(const Game &other) {
        deck = other.deck;
        // player1 = other.player1;
        // player2 = other.player2;
        players = other.players;
        roundBet = other.roundBet;
        table = other.table;
        window = other.window;
        return *this;
    }

    void Game::handleTextInput() {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::TextEntered) {
                // Handle text input
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && inputText.getString().getSize() > 0) {
                        // Backspace key, remove last character
                        std::string currentString = inputText.getString();
                        currentString.pop_back();
                        inputText.setString(currentString);
                    } else if (event.text.unicode != 13) {  // Ignore Enter key
                        inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }
        }
    }


    void Game::drawGame() {
        window->clear(sf::Color{0,122,44});
        window->draw(player1Sum);
        window->draw(player2Sum);
        window->draw(textRoundPot);
        window->draw(textRoundBet);
        window->draw(promptText);
        window->draw(inputBox);
        window->draw(inputText);

        if (!inputText.getString().isEmpty()) {
            sf::Text betText;
            betText.setFont(font);
            betText.setString("P1 Bet: " + inputText.getString());
            betText.setCharacterSize(30);
            betText.setFillColor(sf::Color::White);
            betText.setPosition(650 - betText.getGlobalBounds().width / 2, 500);
            window->draw(betText);
        }

        // de adaugat display la carti

        window->display();
    }

    void Game::updateSums() {
        player1Sum.setString("Suma P1: " + std::to_string(players[0]->getSum()));
        player2Sum.setString("Suma P2: " + std::to_string(players[1]->getSum()));
    }

    void Game::bettingHuman() {
        inputBet = inputText.getString();
        int playerBet = 0;
        // std::cout << "Player 1: ";
        // std::cin >> playerBet;
        // std::cout << std::endl;
        try {
            playerBet = std::stoi(inputBet);
        }
        catch (const std::invalid_argument&) {
            return;
        }
        if(playerBet > players[0]->getSum()) {
            throw NotEnoughFundsExcept("Error: the player does not have enough credits for this bet");
        }
        if(playerBet < 0) {
            throw BetInputInvalidExcept("Error: bet value is invalid");
        }
        players[0]->subtractBet(playerBet);
        players[2]->addSum(playerBet);
        updateSums();

        sf::Text playerBetText;
        playerBetText.setFont(font);
        playerBetText.setString("P1 Bet: " + std::to_string(playerBet));
        playerBetText.setCharacterSize(30);
        playerBetText.setFillColor(sf::Color::White);
        playerBetText.setPosition(650 - playerBetText.getGlobalBounds().width / 2, 400);

        window->draw(playerBetText);
        sf::sleep(sf::seconds(1));

        botBet = false;
        humanBet = true;
    }

    void Game::bettingBot() {
        if (botBet) {
            return;
        }
        int playerBet = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 500);
        playerBet = distrib(gen);
        if(playerBet > players[1]->getSum()) {
            // throw NotEnoughFundsExcept("Error: the player does not have enough credits for this bet");
            playerBet = players[1]->getSum();
        }
        std::cout << "Player 2: " << playerBet << std::endl;

        players[1]->subtractBet(playerBet);
        players[2]->addSum(playerBet);
        updateSums();

        sf::Text botBetText;
        botBetText.setFont(font);
        botBetText.setString("P2 bet: " + std::to_string(playerBet));
        botBetText.setCharacterSize(30);
        botBetText.setFillColor(sf::Color::White);
        botBetText.setPosition(650 - botBetText.getGlobalBounds().width / 2, 500);
        // botBetText.setPosition(650, 250);

        window->draw(botBetText);
        // window->display();
        sf::sleep(sf::seconds(1));

        botBet = true;
    }


    void Game::bettingRound() {

        if(dynamic_cast<HumanPlayer*>(players[0]) && botBet && !humanBet) bettingHuman();

        sf::sleep(sf::seconds(1));

        if(dynamic_cast<BotPlayer*>(players[1]) && !botBet && humanBet) bettingBot();

        sf::sleep(sf::seconds(1));


        /*
        int playerBetHuman = 0;
        std::cout << "Player 1: ";
        std::cin >> playerBetHuman;
        std::cout << std::endl;
        if(playerBetHuman > players[0]->getSum()) {
            throw NotEnoughFundsExcept("Error: the player does not have enough credits for this bet");
        }
        if(playerBetHuman < 0) {
            throw BetInputInvalidExcept("Error: bet value is invalid");
        }
        players[0]->subtractBet(playerBetHuman);
        players[2]->addPot(playerBetHuman);
        updateSums();

        int playerBetBot = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 500);
        playerBetBot = distrib(gen);
        if(playerBetBot > players[1]->getSum()) {
            throw NotEnoughFundsExcept("Error: the player does not have enough credits for this bet");
        }
        std::cout << "Player 2: " << playerBetBot << std::endl;

        players[1]->subtractBet(playerBetBot);
        players[2]->addPot(playerBetBot);

        updateSums();
        */
    }

    void Game::resetRound() {
        table.clearTable();
        players[0]->clearHand();
        players[1]->clearHand();
        deck.resetDeck();
        botBet = false;
    }

    // aici se dau cartile playerilor, in maniera 1-2-1-2
    void Game::dealHands() {
        for(int i = 0; i < 2; i++) {
            players[0]->addCard(deck.dealCard());
            players[1]->addCard(deck.dealCard());
        }

    }

    void Game::displayHand() {
        int i = 1;
        for(auto const &card : players[0]->getPlayerCards()) {
            sf::Sprite sprite = card.getSprite();
            sprite.setPosition(100 * i, 100);
            window->draw(sprite);
            i++;
        }
    }

    // repriza 1 carti
    void Game::dealFlop() {
        for(int i = 0; i < 3; i++) {
            table.addCard(deck.dealCard());
        }
    }

    void Game::displayFlop() {
        int i = 1;
        for (auto const &card : table.getTableCards()) {
            sf::Sprite sprite = card.getSprite();
            sprite.setPosition(100 * i, 400);
            window->draw(sprite);
            i++;
        }

    }

    // reprizele 2 si 3 carti
    // turn si river puteau fi facute separat, dar e exact aceeasi cerinta
    void Game::dealTurnRiver() {
        table.addCard(deck.dealCard());
    }

    void Game::displayTurn() {
        std::vector<Card> cards = table.getTableCards();
        sf::Sprite sprite = cards[3].getSprite();
        sprite.setPosition(100 * 4, 400);
        window->draw(sprite);
    }

    void Game::displayRiver() {
        std::vector<Card> cards = table.getTableCards();
        sf::Sprite sprite = cards[4].getSprite();
        sprite.setPosition(100 * 5, 400);
        window->draw(sprite);
    }


    // verifica daca sunt 5 sau mai multe de acelasi suit
    // flush, straight flush, royal flush
    bool Game::isFlush(const std::vector<int>& suitCount) {
        for (int i = 0; i < 4; i++) {
            if(suitCount[i] >= 5) {
                return true;
            }
        }
        return false;
    }

    // verificare straight
    // straight, straight flush
    bool Game::isStraight(const std::vector<int> &rankCount) {
        int counter = 0;
        for (int i = 0; i < 13; i++) {
            if(rankCount[i] > 0) {
                counter++;
            }
            else counter = 0;

            if (counter == 5) return true;
        }
        return false;
    }

    int Game::getMaxCount(const std::vector<int> &rankCount) {
         int maxCount = 0;
         for (int i = 0; i < 13; i++) {
             if(rankCount[i] > maxCount) maxCount = rankCount[i];
         }
         return maxCount;
    }

    bool Game::isTwoPair(const std::vector<int> &rankCount) {
        int counter = 0;
            for(int i = 0; i < 13; i++) {
                if(getMaxCount(rankCount) == 2) {
                    counter++;
                }
            }
        if (counter == 2) return true;
        return false;
    }

    int Game::getIndexRank(const std::string &rank) {
        if(rank == "2") return 0;
        if(rank == "3") return 1;
        if(rank == "4") return 2;
        if(rank == "5") return 3;
        if(rank == "6") return 4;
        if(rank == "7") return 5;
        if(rank == "8") return 6;
        if(rank == "9") return 7;
        if(rank == "10") return 8;
        if(rank == "J") return 9;
        if(rank == "Q") return 10;
        if(rank == "K") return 11;
        if(rank == "A") return 12;
        return -1;
    }

    int Game::getIndexSuit(const std::string &suit) {
        if(suit == "HEARTS") return 0;
        if(suit == "DIAMONDS") return 1;
        if(suit == "CLUBS") return 2;
        if(suit == "SPADES") return 3;
        return -1;
    }

    int Game::highCardEvaluate(const Player& player) {
        // ia cartile din table si player si face 2 stash uri de carti pentru ambii playeri
        std::vector<Card> allCards = player.getPlayerCards();
        for (const auto& card : table.getTableCards()) {
            allCards.emplace_back(card);
        }

        // numarare de suit uri si rank uri in ambele grupari de 7 carti

        std::vector<int> rankCount(13, 0);
        std::vector<int> suitCount(4, 0);

        for (const auto &card : allCards) {
            int rankIndex = getIndexRank(card.getRank());
            if (rankIndex != -1) rankCount[rankIndex]++;

            int suitIndex = getIndexSuit(card.getSuit());
            if(suitIndex != -1) suitCount[suitIndex]++;
        }

        int highCardVal = -1;
        for (int i = 12; i >= 0; i--) {
            if (rankCount[i]) {
                highCardVal = i;
                break;
            }
        }
        return highCardVal;
    }

    int Game::cardGroupsEvaluate(const Player& player) {
        // ia cartile din table si player si face 2 stash uri de carti pentru ambii playeri
        std::vector<Card> allCards = player.getPlayerCards();
        for (const auto& card : table.getTableCards()) {
            allCards.emplace_back(card);
        }

        // numarare de suit uri si rank uri in ambele grupari de 7 carti

        std::vector<int> rankCount(13, 0);
        std::vector<int> suitCount(4, 0);

        for (const auto &card : allCards) {
            int rankIndex = getIndexRank(card.getRank());
            if (rankIndex != -1) rankCount[rankIndex]++;

            int suitIndex = getIndexSuit(card.getSuit());
            if(suitIndex != -1) suitCount[suitIndex]++;
        }

        // int highCard = highCardEvaluate(allCards, rankCount, suitCount);

        int handValue = 0; // standard, in caz de e doar high card

        // royal flush = straight + flush + verif 1 dintre carti este A rankCount[13]                   value=9 x
        // straight flush = straight + flush                                                            value=8 x
        // four of a kind = counter de 4                                                                value=7 x
        // full house = 3 si 2, caz particular -- trebuie scoasa una dintre grupari si gasita cealalta  value=6 x
        // flush = flush true                                                                           value=5 x
        // straight = straight true                                                                     value=4 x
        // three of a kind = counter de 3                                                               value=3 x
        // two pair = 2 si 2, caz particular -- trebuie scoasa una dintre grupari si gasita cealalta    value=2 x
        // pair = counter de 2                                                                          value=1 x
        // high card = variabila separata retinuta oricum                                               value=0 x

        // idee: fiecare din urmatoarele if case uri poate sa retina si cartile ce intra in componenta gruparii de 5

        // pair value 1 // idee: poate include subcazuri pentru two pair si full house dupa eliminarea celor 2 carti din pair
        if(getMaxCount(rankCount) == 2) {
            handValue = 1;
        }

        // two pair value 2
        if(isTwoPair(rankCount) == true) {
            handValue = 2;
        }

        // three of a kind value 3
        if(getMaxCount(rankCount) == 3) {
            // full house 6
            if(handValue == 1) {
                handValue = 6;
            }
            else handValue = 3;
        }

        if (isStraight(rankCount) == true) {
            handValue = 4; // straight
        }

        if (isFlush(suitCount) == true) {
            handValue = 5; // flush
        }

        // four of a kind value 7
        if (getMaxCount(rankCount) == 4) {
            handValue = 7;
        }


        if (isFlush(suitCount) == true && isStraight(rankCount) == true) {
            if (rankCount[13]) handValue = 9; // royal flush
            else handValue = 8; //straight flush
        }

        return handValue;
    }

    std::ostream& operator<<(std::ostream& os, const Game &game) {
        os << game.players[0] << std::endl;
        os << game.players[1] << std::endl;
        os << game.players[2] << std::endl;
        os << game.table << std::endl;
        return os;
    }

    // functia jocului propriu zis
    void Game::play() {
        while(window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if(players[0]->getSum() > 0 && players[1]->getSum() > 0) {
                    handleTextInput();
                    drawGame();

                    // se dau cartile jucatorilor
                    dealHands();
                    displayHand();

                    // humanBet = false;

                    std::cout << std::endl << "Jucator 1:" << std::endl;
                    std::cout << players[0]->getSum() << std::endl;

                    std::cout << std::endl << "Jucator 2:" << std::endl;
                    std::cout << players[1]->getSum() << std::endl;

                    humanBet = false;
                    bettingRound(); // de revizuit unde se adauga ca sa functioneze jocul cum trebuie
                    std::cout << roundBet << std::endl;
                    std::cout << inputBet << std::endl;

                    std::cout << "Repriza 1 / Flop" << std::endl;
                    dealFlop(); // adauga 3 carti pe masa
                    std::cout << table << std::endl;

                    displayFlop();

                    humanBet = false;
                    bettingRound();
                    std::cout << roundBet << std::endl;
                    std::cout << inputBet << std::endl;

                    // afisari test
                    std::cout << "Repriza 2 / Turn" << std::endl;
                    dealTurnRiver(); // adauga o carte pe masa
                    std::cout << table << std::endl;

                    displayTurn();

                    humanBet = false;
                    bettingRound();
                    std::cout << roundBet << std::endl;
                    std::cout << inputBet << std::endl;

                    std::cout << "Repriza 3 / River" << std::endl;
                    dealTurnRiver(); // adauga o carte pe masa
                    std::cout << table << std::endl;

                    displayRiver();

                    int handValueP1 = cardGroupsEvaluate(*players[0]);
                    int handValueP2 = cardGroupsEvaluate(*players[1]);

                    std::cout << "Hand Value p1: " << std::endl << handValueP1 << std::endl;
                    std::cout << "Hand value p2: " << std::endl << handValueP2 << std::endl;

                    if (handValueP1 > handValueP2) {
                        std::cout << "P1 win" << std::endl;
                        players[0]->addSum(players[2]->getPot());
                    }
                    else if (handValueP1 < handValueP2) {
                        std::cout << "P2 win" << std::endl;
                        players[1]->addSum(players[2]->getPot());
                    }
                    else {
                        int highCardP1 = highCardEvaluate(*players[0]);
                        int highCardP2 = highCardEvaluate(*players[1]);

                        if (highCardP1 > highCardP2) {
                            std::cout << "P1 win" << std::endl;
                            players[0]->addSum(players[2]->getPot());
                        }
                        else if (highCardP1 < highCardP2) {
                            std::cout << "P2 win" << std::endl;
                            players[1]->addSum(players[2]->getPot());
                        }
                        else {
                            std::cout << "Tie" << std::endl;
                            players[0]->addSum((players[2]->getPot()) / 2);
                            players[1]->addSum((players[2]->getPot()) / 2);
                        }
                    }
                    resetRound();
                }
            }
        }
    }