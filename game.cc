#include "game.h"


game::game(std::default_random_engine seed, char* player_types, int num):
    seed{seed} {
        num_of_players = num;
        players = new player* [4];
        for (int i = 0; i < 4; ++i) {
            if (player_types[i] == 'h') {
                players[i] = new human{};
                players[i]->setPlayer_num(i + 1);
            }
            else if (player_types[i] == 'c') {
                players[i] = new cpu{};
                players[i]->setPlayer_num(i + 1);
            }
        }
        spades = new pile{'S'};
        hearts = new pile{'H'};
        clubs = new pile{'C'};
        diamonds = new pile{'D'};
        cards = new deck{};
    
}
game::~game() {
    for (int i = 0; i < num_of_players; ++i) {
        delete players[i];
    }
    delete[] players;
    delete cards;
    delete spades;
    delete hearts;
    delete clubs;
    delete diamonds;
}

bool game::loser_exists() {
    bool loser_exists = false;
    for (int i = 0; i < num_of_players; ++i) {
        if (players[i]->score >= 80) {
            loser_exists = true;
        }
    }
    return loser_exists;
}

int game::first_player() {
    for (int i = 0; i < num_of_players; ++i) {
        for (int j = 0; j < 13; ++j) {
            if (!players[i]->hand[j]->getName().compare("7S")) {
                return i;
            } 
        }
    }
    return -1;
}

void game::clean_hands() {
    for (int i = 0; i < num_of_players; ++i) {
        for (card* c: players[i]->hand) {
            delete c;
        }
        players[i]->hand.clear();
    }
}

void game::clean_discard() {
    for (int i = 0; i < num_of_players; ++i) {
        for (card* c: players[i]->discard_pile) {
            delete c;
        }
        players[i]->discard_pile.clear();
    }
}

bool game::all_cards_played() {
    bool all_empty = true;
    for (int i = 0; i < num_of_players; ++i) {
        if (!players[i]->hand.empty()) {
            all_empty = false;
            break;
        }
    }
    return all_empty;
}

void game::discards_and_update_score(){
    for (int i = 0; i < num_of_players; ++i) {
        int added_score = 0;
        // Player<x>’s discards:<list of discards>
        cout << "Player<" << players[i]->getPlayer_num() << "’s discards: ";
        for (card* c: players[i]->discard_pile) {
            cout << c->getName() << " ";
            added_score += c->getValue();
        }
        cout << endl;
        
        // Player<x>’s score: <old score> + <score gained> = <new score>
        cout << "Player<" << players[i]->getPlayer_num() << "’s score: " << players[i]->score << " + " << added_score << " = " << players[i]->score + added_score << endl;
        players[i]->score += added_score;
    }
}

void game::deal() {
    int hand_size = 13;
    for (int i = 0; i < hand_size; ++i) {
        players[0]->hand.push_back(cards->cards[i]);
        cards->cards[i] = nullptr;
    }
    for (int i = hand_size; i < hand_size*2; ++i) {
        players[1]->hand.push_back(cards->cards[i]);
        cards->cards[i] = nullptr;
    }
    for (int i = hand_size*2; i < hand_size*3; ++i) {
        players[2]->hand.push_back(cards->cards[i]);
        cards->cards[i] = nullptr;
    }
    for (int i = hand_size*3; i < hand_size*4; ++i) {
        players[3]->hand.push_back(cards->cards[i]);
        cards->cards[i] = nullptr;
    }
}

void game::resetPiles() {
    for (card* s: spades->cards) {
        delete s;
        spades->valid_card_top = 0;
        spades->valid_card_bot = 0;
    }
    spades->cards.clear();
    for (card* h: hearts->cards) {
        delete h;
        hearts->valid_card_top = 0;
        hearts->valid_card_bot = 0;
    }
    hearts->cards.clear();
    for (card* c: clubs->cards) {
        delete c;
        clubs->valid_card_top = 0;
        clubs->valid_card_bot = 0;
    }
    clubs->cards.clear();
    for (card* d: diamonds->cards) {
        delete d;
        diamonds->valid_card_top = 0;
        diamonds->valid_card_bot = 0;
    }
    diamonds->cards.clear();
}

void game::rageQuit(int player_num) {
    player* comp = new cpu{};
    for (card* c: players[player_num]->hand) {
        comp->hand.push_back(c);
    }
    for (card* d: players[player_num]->discard_pile) {
        comp->discard_pile.push_back(d);
    }
    for (card* l: players[player_num]->legal_plays) {
        comp->hand.push_back(l);
    }
    delete players[player_num];
    players[player_num] = comp;
}


void game::playGame() {
    while(1) {
        if (loser_exists()) {
            int lowest_score = players[0]->score;
            for (int i = 1; i < 4; ++i) {
                if (players[i]->score < lowest_score) {
                    lowest_score = players[i]->score;
                }
            }
            for (int i = 0; i < 4; ++i) {
                if (players[i]->score == lowest_score) {
                    cout << "Player" << i+1 << " wins!" << endl;
                }
            }
            break;
        }
        cards->shuffle(seed); //shuffling cards
        cards->saveState(); // saving state
        deal(); //dealing cards
        int players_turn = first_player();
        cout << "A new round begins. It’s Player" << players_turn + 1 << "’s turn to play." << endl;
        cout << "Cards on the table:" << endl;
        cout << "Clubs: " << endl;
        cout << "Diamonds: " << endl;
        cout << "Hearts: " << endl;
        cout << "Spades: " << endl;
        players[players_turn]->play7S(cards, spades);
        if (stop == true) {
            discards_and_update_score();
            resetPiles();
            cards->resetDeck();
            clean_hands();
            clean_discard();
            return;
        }
        if (players_turn == 3) {
                players_turn = 0;
        }
        else {
            ++players_turn;
        }
        while (1) {
            if (all_cards_played()) {
                break;
            }
            cout << "Cards on the table:" << endl;
            cout << "Clubs: ";
            for (card* c: clubs->cards) {
                cout << c->getRank() << " ";
            }
            cout << endl;
            cout << "Diamonds: ";
            for (card* c: diamonds->cards) {
                cout << c->getRank() << " ";
            }
            cout << endl;
            cout << "Hearts: ";
            for (card* c: hearts->cards) {
                cout << c->getRank() << " ";
            }
            cout << endl;
            cout << "Spades: ";
            for (card* c: spades->cards) {
                cout << c->getRank() << " ";
            }
            cout << endl;
            
            
            players[players_turn]->play(cards, spades, hearts, clubs, diamonds);
            if (stop == true) {
                discards_and_update_score();
                resetPiles();
                cards->resetDeck();
                clean_hands();
                clean_discard();
                return;
            }
            if (players_turn == 3) {
                players_turn = 0;
            }
            else {
                ++players_turn;
            }
        }
        discards_and_update_score();
        resetPiles();
        cards->resetDeck();
        clean_hands();
        clean_discard();
    }
}















