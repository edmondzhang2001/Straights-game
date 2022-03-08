#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
using namespace std;


class card {
    protected:
        string name;
        char rank;
        char suit;
        int value;
    public:
        card(char suit, int value);
        card(const card &other);
        string getName() const { return name; }
        char getRank() const { return rank; }
        char getSuit() const { return suit; }
        void setSuit(char s) { suit = s; }
        void setRank(int r) { rank = r; };
        int getValue() const { return value; }
};

#endif