#include "deck.h"
#include <iostream>
#include <vector>
#include <algorithm>



void deck::saveState() {
    for(card* c: previousState) {
        delete c;
    }
    previousState.clear();
    for (int i = 0; i < capacity; ++i) {
        previousState.push_back(new card{ *cards[i] });
    }
}

deck::deck() {
    capacity = 52;
    char suits[4] = { 'S', 'H', 'C', 'D'};
    for (int i = 0; i < 4; i++) {
        for (int r = 1; r <= 13; r++) {
            cards.push_back(new card(suits[i], r));
        }
    }
    this->saveState();
}

deck::~deck() {
    for (card* c : cards) {
        delete c;
    }
    cards.clear();
    for (card* p : previousState) {
        delete p;
    }
    previousState.clear();
}

void deck::displayDeck() {
    for (int i = 1; i <= capacity; ++i) {
        if (i % 13 == 0) {
            cout << previousState[i-1]->getName() << endl;
        }
        else {
            cout << previousState[i-1]->getName() << ' ';
        }
    }
}

void deck::shuffle(std::default_random_engine seed) {
    std::shuffle(previousState.begin(), previousState.end(), seed);
    for (card* c: cards) {
        delete c;
    }
    cards.clear();
    for (int i = 0; i < capacity; ++i) {
        cards.push_back(new card{ *previousState[i] });
    }
}

void deck::resetDeck() {
    for (card* c: cards) {
        delete c;
    }
    cards.clear();
}
