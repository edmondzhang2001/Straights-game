#include "pile.h"

pile::pile(char suit):
    suit{suit} {
        valid_card_bot = -1;
        valid_card_top = -1;
    };

pile::~pile() {
    for (card* c : cards) {
        delete c;
    }
    cards.clear();
}


void addToPile(card* c);
bool valid_check();