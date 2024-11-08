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
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Milestone #2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] tag de `git`: de exemplu `v0.2`

## Milestone #3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
