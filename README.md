# Texas Hold' em

*O variantă de poker, popularizată în anii recenți.*
*Acum, cu mai puține pariuri!*

### Reguli generale

Jocul are loc în format 1v1, fiecare jucător primind în mână două cărți.
Pe masa de joc sunt puse cinci cărți, în trei reprize: prima repriză cu trei cărți, numit *flop*, a doua repriză cu o carte, numit *turn*, și a treia repriză cu ultima carte, numit *river*.

Jucătorul cu cea mai bună formațiune de cinci cărți, ce le include și pe cele din mâna lui, câștigă.

Rezultatul jocului este determinat într-o manieră de „best of three”, adică cel cu cele mai multe câștiguri în trei runde este învingător.

Formațiuni de cărți câștigătoare, în ordine crescătoare:
* ___High card___ (un set de cinci cărți oarecare, se ia în considerare cartea cu cea mai mare valoare)
* ___One Pair___ (două cărți cu aceeași valoare)
* ___Two Pairs___ (două perechi de cărți cu aceeași valoare)
* ___Three of a Kind___ (trei cărți cu aceeași valoare)
* ___Straight___ (valorile tuturor cărților în ordine crescătoare)
* ___Flush___ (toate cărțile sunt de același tip/culoare)
* ___Full House___ (trei de un fel și o pereche)
* ___Four of a Kind___ (patru cărți de aceeași valoare)
* ___Straight Flush___ (toate cărțile în ordine crescătoare și de același tip/culoare)
* ___Royal Flush___ (toate cărțile în ordine crescătoare, de același tip/culoare, de la _10_ la _A_)


## Milestone #0

- [x] Nume proiect
- [x] Scurtă descriere a temei alese

## Milestone #1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [x] constructori de inițializare cu parametri
- [x] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [x] scenariu de utilizare a claselor definite:
  - preferabil sub formă de teste unitare, mai ales dacă vorbim de aplicații consolă 
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Milestone #2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [x] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [x] tag de `git`: de exemplu `v0.2`

## Milestone #3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
- [x] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [x] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- [CARD SPRITES](https://opengameart.org/content/playing-cards-vector-png) (Author: Byron Knoll)
- [FIGMA COLOR WHEEL](https://www.figma.com/color-wheel/)
- [Informatii despre tie-breaker pentru jocul de poker](https://www.blitzpoker.com/blogs/texas-holdem-tie-breaker/)
- Fonturi:
  - [Babel-Sans](https://www.dafont.com/babel-sans.font)
  - [Bleeding Cowboys](https://www.dafont.com/bleeding-cowboys.font) (PERSONAL USE!)
  - [Bronco](https://www.dafont.com/bronco.font) (PERSONAL USE!)
- Alte link-uri ajutatoare:
  - [Sortare de vector de obiecte](https://stackoverflow.com/questions/34385586/sort-vector-of-class-objects-based-on-some-member-variable)
  - [Random shuffle](https://en.cppreference.com/w/cpp/algorithm/random_shuffle)
  - [SFML Shapes](https://www.sfml-dev.org/documentation/2.6.2/classsf_1_1Shape.php)
  - [Render pentru o imagine de fundal](https://stackoverflow.com/questions/36448101/2-3-1-set-scale-of-background-texture-to-renderwindow-size)
  - [Culori in SFML](https://learnsfml.com/basics/graphics/how-to-use-colors-in-sfml/)
  - [Randomizare de numere](https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution)
  - [Convertire SFML Text la std::string](https://stackoverflow.com/questions/38082453/sfml-getting-text-from-sftext)
- [...]