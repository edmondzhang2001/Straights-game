#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>
#include <algorithm>
#include <random>

class deck {
    public:
        int capacity;
        std::vector<card *> cards;
        std::vector<card *> previousState;
    
    public:
        deck();
        ~deck();
        void resetDeck();
        void shuffle(std::default_random_engine seed);
        void saveState();
        void displayDeck();
};

#endif