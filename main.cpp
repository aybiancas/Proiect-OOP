#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class Menu {
    std::vector<std::string> options = {"Start", "Reguli", "Iesi"};



    public:
    Menu() = default;
    ~Menu() = default;

    void showMenu() {
        std::cout << "Texas Hold' em" << std::endl;
        for(int i = 0; i<options.size(); i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
    }

    void selectOption() {
        int choice;
        std::cout << "Optiune: ";
        std::cin >> choice;

        // vezi la selectarea de optiuni cum faci if else case urile

        switch (choice) {
            case 1:
                std::cout << "Incepe jocul ..." << std::endl;
            break;
            case 2:
                showRules();
            break;
            case 3:
                std::cout << "Se inchide ..." << std::endl;
            break;
            default:
                std::cout << "Invalid ..." << std::endl;
        }
    }
    void showRules () {
        // apeleaza fisierul de citit de reguli si le afiseaza
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Menu& menu) {
            os << "Options:" << std::endl;
            for (int i = 0; i < menu.options.size(); i++) {
                os << i + 1 << ". " << menu.options[i] << std::endl;
            }
            return os;
        }
};

class Card {
    std::string suit;
    std::string rank;

    public:
    // constr param cu lista de init
    Card(const std::string &suit, const std::string &rank) : suit(suit), rank(rank) {}


    // constr de copiere cu lista
    Card(const Card &other) : suit(other.suit), rank(other.rank) {}


    // getteri
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
        os << card.rank << " of " << card.suit << std::endl;
        return os;
    }
};

class Deck {
    std::vector<Card> cards;
    std::vector<std::string> suits = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"};
    std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    // idee: fa toate cardurile string uri de genul doi, trei, patru just for display purposes

    public:
    Deck() {
        for (const auto &suit : suits) {
            for (const auto &rank : ranks) {
                cards.emplace_back(suit, rank);
            }
        }
    }

    // amestecare deck
    // singura varianta de shuffle care imi merge
    void shuffleCards () {
        std::default_random_engine d(std::random_device{}());
        std::shuffle(cards.begin(), cards.end(), d);
    }

    // doar de verificare, nu e apelata propriu zis in joc
    void printCards () {
        for (const auto &card : cards) {
            std::cout << card.getRank() << " of " << card.getSuit() << std::endl;
        }
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream &os, const Deck &deck) {
        for (const auto &card : deck.cards) {
            os << card << std::endl;
        }
        return os;
    }

    // scoate carte din deck
    Card dealCard () {
        Card cardsDealt = cards.back();
        cards.pop_back();
        return cardsDealt;
    }
};

class Hand {
    std::vector<Card> cards;

    public:

    // pune carte in mana
    void addCard (const Card &card) {
        cards.push_back(card);
    }

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Hand& hand) {
        for (const auto &card : hand.cards) {
            os << card << std::endl;
        }
        return os;
    }

};

class TableCards {
    std::vector<Card> cards;

    public:

    void addCard (const Card &card) {
        cards.push_back(card);
    }

    void clearCards () {
        cards.clear();
    }

    friend std::ostream& operator<<(std::ostream& os, const TableCards& table) {
        os << "Carti pe masa: " << std::endl;
        for (const auto &card : table.cards) {
            os << card << std::endl;
        }
        return os;
    }

};

class Game {
    Deck deck;
    Hand player1Hand;
    Hand player2Hand;
    TableCards table;

    public:
    Game() {
        // apelare shuffle de 5 ori doar pentru ca o singura data era prea putin distribuit
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
        deck.shuffleCards();
    }

    void dealHands () {
        for(int i = 0; i < 2; i++) {
            player1Hand.addCard(deck.dealCard());
            player2Hand.addCard(deck.dealCard());
        }
    }

    void dealFlop () {
        for(int i = 0; i < 3; i++) {
            table.addCard(deck.dealCard());
        }
    }

    void dealTurnRiver () {
        table.addCard(deck.dealCard());
    }

    void play() {
        dealHands();
        std::cout << std::endl << "Jucator 1:" << std::endl;
        std::cout << player1Hand << std::endl;

        // std::cout << std::endl << "Jucator 2:" << std::endl;
        // std::cout << player2Hand << std::endl;

        std::cout << "Repriza 1 / Flop" << std::endl;
        dealFlop();
        std::cout << table << std::endl;

        std::cout << "Repriza 2 / Turn" << std::endl;
        dealTurnRiver();
        std::cout << table << std::endl;

        std::cout << "Repriza 3 / River" << std::endl;
        dealTurnRiver();
        std::cout << table << std::endl;

    }
};


int main() {
    Game game;
    game.play();
    return 0;
}

    // Menu menu;
    // menu.showMenu();
    // menu.selectOption();

    // Deck deck;
    // strict pentru verificare
    // std::cout << "Carti:" << std::endl;
    // deck.printCards();

    // apelare shuffle de 4 ori doar pentru ca o singura data era prea putin distribuit
    // deck.shuffleCards();
    // deck.shuffleCards();
    // deck.shuffleCards();
    // deck.shuffleCards();
    // std::cout << std::endl << "Shuffle:" << std::endl;
    // deck.printCards();
    //
    // Hand player1Hand;
    // Hand player2Hand;
    //
    // for(int i = 0; i < 2; i++) {
    //     player1Hand.addCard(deck.dealCard());
    //     player2Hand.addCard(deck.dealCard());
    // }
    //
    // std::cout << std::endl << "Jucator 1:" << std::endl;
    // std::cout << player1Hand << std::endl;
    //
    // std::cout << std::endl << "Jucator 2:" << std::endl;
    // std::cout << player2Hand << std::endl;



    // std::cout << "Hello, world!\n";
    // std::array<int, 100> v{};
    // int nr;
    // std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    // std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "v[" << i << "] = ";
    //     std::cin >> v[i];
    // }
    // std::cout << "\n\n";
    // std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    // for(int i = 0; i < nr; ++i) {
    //     std::cout << "- " << v[i] << "\n";
    // }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    // Helper helper;
    // helper.help();
    ///////////////////////////////////////////////////////////////////////////

