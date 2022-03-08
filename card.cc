#include "card.h"
#include <string>
#include <sstream>

using namespace std;

card::card(char suit, int value):
    suit{suit}, value{value} {
        if (value == 1) {
            this->rank = 'A';
        }
        else if (value == 10) {
            this->rank = 'T';
        }
        else if (value == 11) {
            this->rank = 'J';
        }
        else if (value == 12) {
            this->rank = 'Q';
        }
        else if (value == 13) {
            this->rank = 'K';
        }
        else {
            this->rank = '0' + value;
        }
        std::stringstream sstm;
        sstm << rank << suit;
        name = sstm.str();
}

card::card(const card &other) {
    this->name = other.name;
    this->value = other.value;
    this->rank = other.rank;
    this->suit = other.suit;
}



