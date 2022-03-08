#ifndef PILE_H
#define PILE_H
#include <vector>
#include "card.h"

class pile {
    private:
        char suit;
    public:
        std::vector<card *> cards;
        int valid_card_top;
        int valid_card_bot;
        pile(char suit);
        ~pile();
        void addToPile(card* c);
        bool valid_check();
};

#endif