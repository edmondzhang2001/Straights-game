#ifndef GAME_H
#define GAME_H
#include "card.h"
#include "player.h"
#include "pile.h"
#include "deck.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class game {
    private:
        std::default_random_engine seed;
        int num_of_players;
        deck* cards;
        player** players;
        pile* spades;
        pile* hearts;
        pile* clubs;
        pile* diamonds;
    public:
        game(std::default_random_engine seed, char* player_types, int num);
        ~game();
        bool loser_exists();
        void playGame();
        int first_player();
        void clean_hands();
        void clean_discard();
        bool all_cards_played();
        void discards_and_update_score();
        void rageQuit(int player_num);
        void deal();
        void resetPiles();
};

#endif