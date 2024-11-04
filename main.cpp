#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>

class Card {
    std::string suit;
    std::string rank;

    public:
    // constructor parametrizat cu lista de initializare
    Card(const std::string &suit, const std::string &rank) : suit(suit), rank(rank) {}

    // constructor de copiere cu lista de initializare
    Card(const Card &other) : suit(other.suit), rank(other.rank) {}

    // destructor
    ~Card() {}

    // getteri pt culoare si valoare
    [[nodiscard]] std::string getSuit() const {
        return suit;
    }

    [[nodiscard]] std::string getRank() const {
        return rank;
    }

    // operator =
    Card& operator= (const Card &other) {
        suit = other.suit;
        rank = other.rank;
        return *this;
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream &os, const Card &card) {
        os << card.rank << " de " << card.suit << std::endl;
        return os;
    }
};

class Deck {
    std::vector<Card> cards;
    std::vector<std::string> suits = {"INIMA", "ROMB", "TREFLA", "PICA"};
    std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    public:
    // deck construit automat ordonat
    Deck() {
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                cards.emplace_back(suit, rank);
            }
        }
        std::cout << "Deck constructor" << std::endl;

        // printDeck();
    }

    // constructor de copiere
    Deck (const Deck &other) : cards(other.cards) {}

    // destructor
    ~Deck() {
        std::cout << "Deck destructor" << std::endl;
    }

    // operator =
    Deck &operator= (const Deck &other) {
        cards = other.cards;
        return *this;
    }

    // doar pentru verificare
    void printDeck () {
        for (const auto &card : cards) {
            std::cout << card << std::endl;
        }
    }

    // getter
    [[nodiscard]] std::vector<Card> getDeckCards() const {
        return cards;
    }

    // amestecare deck
    void shuffleCards () {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream &os, const Deck &deck) {
        for (const auto &card : deck.cards) {
            os << card << std::endl;
        }
        return os;
    }

    // scoate carte din deck -- de la sfarsit -- folosita cand se dau cartile playerilor si cand se pun pe masa
    Card dealCard () {
        Card cardsDealt = cards.back();
        cards.pop_back();
        return cardsDealt;
    }
};

// player
class Player {
    std::vector<Card> cards;
    int sum; // suma playerului, utilizata ulterior in sistemul de betting -- cand suma unui player ajunge la 0 acela pierde

    public:

    // constructor cu lista de initializare, suma standard e de 500, playerul incepe in statusul de folded = false
    Player() : sum(500) {
        std::cout << "Player constructor" << std::endl;
    }

    // constructor de copiere
    Player (const Player &other) : cards(other.cards), sum(other.sum) {}

    // destructor
    ~Player() {
        std::cout << "Player destructor" << std::endl;
    }

    // operator =
    Player &operator= (const Player &other) {
        cards = other.cards;
        sum = other.sum;
        return *this;
    }

    // getter
    [[nodiscard]] std::vector<Card> getPlayerCards() const {
        return cards;
    }

    // pune carte in cartile din mana
    void addCard (const Card& card) {
        cards.push_back(card);
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        for (const auto &card : player.cards) {
            os << card << std::endl;
        }
        return os;
    }

};

class TableCards {
    std::vector<Card> cards;

    public:
    // constructor
    TableCards() {
        std::cout << "Masa constructor" << std::endl;
    }

    // constructor de copiere
    TableCards (const TableCards &other) : cards(other.cards) {}

    // destructor
    ~TableCards() {
        std::cout << "Masa destructor" << std::endl;
    }

    // operator =
    TableCards &operator= (const TableCards &other) {
        cards = other.cards;
        return *this;
    }

    // getter
    [[nodiscard]] std::vector<Card> getTableCards() const {
        return cards;
    }

    // adauga cartea in vectorul de carti de pe masa
    void addCard (const Card& card) {
        cards.push_back(card);
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const TableCards& table) {
        os << "Carti pe masa: " << std::endl;
        for (const auto &card : table.cards) {
            os << card << std::endl;
        }
        return os;
    }

};

// De adaugat logica joc:
// evaluatorul de carti si definirea unui handValue pentru a decide ce grupare este mai buna
// + tiebreaker
// implementarea de ture
// ideea de call, raise, fold pentru player 1
// + functie de all in pt raise
// + caz pt call in care unul din playeri nu are suma necesara pt call -- automat fold
// automat implementare de suma pentru betting (~500/1000?) si oprirea jocului cand un player are suma = 0

class Game {
    Deck deck;
    Player player1;
    Player player2;
    TableCards table;
    int pot;
    int roundBet;
    std::vector<std::string> handTypes =
        {"High Card", "One Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush"};


    public:

    // constructor joc
    Game() : pot(0), roundBet(0) {
        // deck ul isi da shuffle automat pentru joc, deoarece e construit ordonat
        // apelare shuffle de 5 ori de siguranta
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
    }

    // constructor de copiere
    Game (const Game &other) : deck(other.deck), player1(other.player1), player2(other.player2), roundBet(other.roundBet), pot(other.pot) {}

    // destructor
    ~Game() {
        std::cout << "Game destructor" << std::endl;
    }

    // operator =
    Game &operator= (const Game &other) {
        deck = other.deck;
        player1 = other.player1;
        player2 = other.player2;
        roundBet = other.roundBet;
        table = other.table;
        pot = other.pot;
        return *this;
    }

    // aici se dau cartile playerilor, in maniera 1-2-1-2
    void dealHands () {
        for(int i = 0; i < 2; i++) {
            player1.addCard(deck.dealCard());
            player2.addCard(deck.dealCard());
        }
    }

    // repriza 1 carti
    void dealFlop () {
        for(int i = 0; i < 3; i++) {
            table.addCard(deck.dealCard());
        }
    }

    // reprizele 2 si 3 carti
    // turn si river puteau fi facute separat, dar e exact aceeasi cerinta
    void dealTurnRiver () {
        table.addCard(deck.dealCard());
    }

    // folosita in evaluarea cartilor din mana si de pe masa
    int getIndexRank (const std::string &rank) const {
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

    // folosita in evaluarea cartilor si de pe masa
    int getIndexSuit (const std::string &suit) const {
        if(suit == "INIMA") return 0;
        if(suit == "ROMB") return 1;
        if(suit == "TREFLA") return 2;
        if(suit == "PICA") return 3;
        return -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const Game &game) {
        os << game.player1 << std::endl;
        os << game.player2 << std::endl;
        os << game.table << std::endl;
        return os;
    }

    // functia jocului propriu zis
    void play() {

        // for(auto &card : deck.getDeckCards()) {
        //     std::cout << card << std::endl;
        // }

        // se dau cartile jucatorilor
        dealHands();

        // afisari de carti din mana, pur de test, vor disparea la adaugarea logicii jocului
        // (in partialitate, mana jucatorului 1 e de fapt userul care joaca)
        std::cout << std::endl << "Jucator 1:" << std::endl;
        std::cout << player1 << std::endl;

        std::cout << std::endl << "Jucator 2:" << std::endl;
        std::cout << player2 << std::endl;

        // acelasi caz ca la maini, afisari pur de test, dispar (in partialitate, cartile de pe masa oricum trebuie sa apara)
        std::cout << "Repriza 1 / Flop" << std::endl;
        dealFlop(); // adauga 3 carti pe masa
        std::cout << table << std::endl;

        // afisari test
        std::cout << "Repriza 2 / Turn" << std::endl;
        dealTurnRiver(); // adauga o carte pe masa
        std::cout << table << std::endl;

        std::cout << "Repriza 3 / River" << std::endl;
        dealTurnRiver(); // adauga o carte pe masa
        std::cout << table << std::endl;

    }
};


class Menu {
    std::vector<std::string> options = {"Start", "Reguli", "Iesi"};
    Game* game;

public:
    Menu() : game(nullptr) {
        std::cout << "Meniu creat." << std::endl;
    }

    Menu (const Menu &other) : options(other.options), game(other.game) {}

    ~Menu() {
        delete game;
        std::cout << "Meniu inchis." << std::endl;
    }

    Menu &operator= (const Menu &other) {
        options = other.options;
        game = other.game;
        return *this;
    }

    // optiuni de meniu
    void showMenu() const {
        std::cout << "Texas Hold' em" << std::endl;
        for(int i = 0; i < options.size(); i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
    }

    // alegerea optiunii de meniu
    void selectOption(int choice) {
        std::cout << "Optiune: ";

        switch (choice) {
            case 1:
                std::cout << "Incepe jocul ..." << std::endl;
            startGame();
            // apelare functie de joc
            break;

            case 2:
                std::cout << "Reguli: [...]" << std::endl;
            showRules();
            // idee: sa ramana in meniu inainte de a inchide meniul
            break;

            case 3:
                std::cout << "Se inchide ..." << std::endl;
            // opreste programul
            break;

            default:
                std::cout << "Invalid ..." << std::endl;
            // in cazul inputului de la user in consola, urmatoarele doua linii de cod comentat merg
            // showMenu();
            // selectOption(choice);
            // afiseaza din nou optiunile din meniu
        }
    }

    void startGame() {
        if (game != nullptr) {
            delete game;
        }

        game = new Game();
        game->play();
    }

    void showRules () {
        // citeste fisierul de reguli si le afiseaza pe ecran
        std::ifstream f("reguli.txt");
        std::string line;
        while (std::getline(f, line)) {
            std::cout << line << std::endl;
        }
        f.close();
        std::cout << std::endl;
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        for (int i = 0; i < menu.options.size(); i++) {
            os << i + 1 << ". " << menu.options[i] << std::endl;
        }
        return os;
    }
};


int main() {
    //test meniu


    std::ifstream f("tastatura.txt");
    int choice;
    f >> choice;
    f.close();

    Menu menu;
    menu.showMenu();
    menu.selectOption(choice);



    // test joc
    // Game game;
    // game.play();
    // return 0;
}
