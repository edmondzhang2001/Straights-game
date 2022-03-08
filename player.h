#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"
#include "pile.h"
#include "deck.h"
using namespace std;

extern bool stop;

class player {
    protected:
        int player_num;
    public:
        std::vector<card *> hand;
        std::vector<card *> discard_pile;
        std::vector<card *> legal_plays;
        int score;
        player();
        virtual ~player();
        void updateLegalPlays();
        virtual void play(deck* d, pile* spades, pile* hearts, pile* clubs, pile* diamonds) = 0;
        void play_card(card* c, pile* p);
        bool legal_play(card* c, pile* p);
        virtual void play7S(deck* d, pile* s) = 0;
        void setPlayer_num(int n) { player_num = n; }
        int getPlayer_num() { return player_num; }
};


class cpu : public player {
    public:
        cpu();
        void play(deck* d, pile* spades, pile* hearts, pile* clubs, pile* diamonds) override;
        void play7S(deck* d, pile* s) override;
};

class human : public cpu {
    public:
        bool ragequitted;
        human();
        void play(deck* d, pile* spades, pile* hearts, pile* clubs, pile* diamonds) override;
        void play7S(deck * d, pile* s) override;
};
#endif