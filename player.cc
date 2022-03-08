#include "player.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

bool stop = false;

player::player() {
    score = 0;
}

player::~player() {
};

bool player::legal_play(card* c, pile* p) {
    if (c->getValue() == p->valid_card_bot || c->getValue() == p->valid_card_top) {
        return true;
    }
    else if (c->getValue() == 7) {
        return true;
    }
    else {
        return false;
    }
}

void player::play_card(card* c, pile* p) {
    cout << "Player" << getPlayer_num() << " plays " << c->getName() << "." << endl;
    if (c->getValue() == 7) {
        p->cards.push_back(c);
        p->valid_card_top = 8;
        p->valid_card_bot = 6;
        
    }
    else if (c->getValue() == p->valid_card_top) {
        p->cards.push_back(c);
        ++p->valid_card_top;
    }
    else if (c->getValue() == p->valid_card_bot) {
        p->cards.insert(p->cards.begin(), c);
        --p->valid_card_bot;
    }
    else {
        cout << "error: invalid card" << endl;
    }
}


//-------------------------------------------------------------------------------

human::human(){
    score = 0;
    ragequitted = false;
}

void human::play7S(deck* d, pile* s) {
    if (ragequitted == true) {
        cout << "test" << endl;
        cpu::play7S(d, s);
    }
    else {
        cout << "Your hand: ";
        for (card* c: hand) {
            cout << c->getName() << " ";
        }
        cout << endl;
        cout << "Legal plays: 7S"<< endl;
        while (1) {
            string command1;
            string command2;
            cin >> command1;
            if (!command1.compare("discard")) {
                cout << "You have a legal play. You may not discard." << endl;
                continue;
            }
            else if (!command1.compare("ragequit")) {
                cout << "Player" << getPlayer_num() << " ragequits. A computer will now take over." << endl;
                ragequitted = true;
                cpu::play7S(d, s);
                break;
            }
            else if (!command1.compare("deck")) {
                d->displayDeck();
                continue;
            }
            else if (!command1.compare("quit")) {
                stop = true;
                return;
            }
            cin >> command2;
            if (!command1.compare("play") && !command2.compare("7S")) {
                card* c;
                int hand_location = 0;
                for (card* h: hand) {
                    if (!h->getName().compare("7S")) {
                        c = h;
                        play_card(c, s);
                        break;
                    }
                    ++hand_location;
                }
                hand.erase(hand.begin() + hand_location);
                break;
            }
            else if (!command1.compare("play")) {
                cout << "This is not a legal play." << endl;
                continue;
            }
            continue;
        }
    }
}

void human::play(deck* d, pile* spades, pile* hearts, pile* clubs, pile* diamonds) {
    if (ragequitted == true) {
        cpu::play(d, spades, hearts, clubs, diamonds);
    }
    else {
        bool legal_play_exists = false;
        legal_plays.clear();
        pile* pile_of_interest;
        for (card* c: hand) {
            if (c->getSuit() == 'S') {
                pile_of_interest = spades;
            }
            else if (c->getSuit() == 'H') {
                pile_of_interest = hearts;
            }
            else if (c->getSuit() == 'C') {
                pile_of_interest = clubs;
            }
            else {
                pile_of_interest = diamonds;
            }
            if (legal_play(c, pile_of_interest)) {
                legal_plays.push_back(c);
                legal_play_exists = true;
            }
            pile_of_interest = nullptr;
        }
        
        //Your hand: 7C QS KH 5S 6S JD AD 7S 8D TD 6D TC KD
        cout << "Your hand: ";
        for (card* c: hand) {
            cout << c->getName() << " ";
        }
        cout << endl;
        
        //Legal plays: 7S
        cout << "Legal plays: ";
        for (card* c: legal_plays) {
            cout << c->getName() << " ";
        }
        cout << endl;
        
        while (1) {
            string command;
            string card_input;
            cin >> command;
            if (!command.compare("play")) {
                cin >> card_input;
                bool valid_card = false;
                card* c;
                int i = 0;
                for (card* h : legal_plays) {
                    if (!h->getName().compare(card_input)) {
                        c = h;
                        valid_card = true;
                        break;
                    }
                    ++i;
                }
                if (valid_card == false) {
                    cout << "This is not a legal play." << endl;
                    continue;
                }
                else {
                    if (c->getSuit() == 'S') {
                    pile_of_interest = spades;
                    }
                    else if (c->getSuit() == 'H') {
                        pile_of_interest = hearts;
                    }
                    else if (c->getSuit() == 'C') {
                        pile_of_interest = clubs;
                    }
                    else {
                        pile_of_interest = diamonds;
                    }
                    play_card(c, pile_of_interest);
                    //removing card from legal plays
                    legal_plays.erase(legal_plays.begin() + i);
                    
                    //removing card played from hand
                    int hand_location = 0;
                    for (card* h : hand) {
                        if (!h->getName().compare(c->getName())) {
                            break;
                        }
                        ++hand_location;
                    }
                    hand.erase(hand.begin() + hand_location);
                    break;
                }
            }
            else if (!command.compare("discard")) {
                cin >> card_input;
                bool valid_card = false;
                if (legal_play_exists == true) {
                    cout << "You have a legal play. You may not discard." << endl;
                }
                else {
                    card* c;
                    int hand_location = 0;
                    for (card* h : hand) {
                        if (!h->getName().compare(card_input)) {
                            c = h;
                            valid_card = true;
                            break;
                        }
                        ++hand_location;
                    }
                    if (valid_card) {
                        cout << "Player" << getPlayer_num() << " discards " << c->getName() << "." << endl;
                        discard_pile.push_back(c);
                        hand.erase(hand.begin() + hand_location);
                        break;
                    }
                    else {
                        cout << "This is not a legal discard." << endl;
                        continue;
                    }
                }
            }
            else if (!command.compare("ragequit")) {
                cout << "Player" << getPlayer_num() << " ragequits. A computer will now take over." << endl;
                ragequitted = true;
                cpu::play(d, spades, hearts, clubs, diamonds);
                break;
            }
            else if (!command.compare("deck")) {
                d->displayDeck();
                continue;
            }
            else if (!command.compare("quit")) {
                stop = true;
                return;
            }
            else {
                continue;
            }
        }
    }
}

//-------------------------------------------------------------------------------
cpu::cpu() {
    score = 0;
}

void cpu::play7S(deck* d, pile* s) {
    card* seven_spades = nullptr;
    int i = 0;
    for (card* c : hand) {
        if (!c->getName().compare("7S")) {
            seven_spades = c;
            break;
        }
        ++i;
    }
    play_card(seven_spades, s);
    hand.erase(hand.begin()+i);
    s->valid_card_bot = 6;
    s->valid_card_top = 8;
}

void cpu::play(deck* d, pile* spades, pile* hearts, pile* clubs, pile* diamonds) {
    bool legal_play_exists = false;
    pile* pile_of_interest;
    int i = 0;
    for (card* c: hand) {
        if (c->getSuit() == 'S') {
            pile_of_interest = spades;
        }
        else if (c->getSuit() == 'H') {
            pile_of_interest = hearts;
        }
        else if (c->getSuit() == 'C') {
            pile_of_interest = clubs;
        }
        else {
            pile_of_interest = diamonds;
        }
        if (legal_play(c, pile_of_interest)) {
            play_card(c, pile_of_interest);
            hand.erase(hand.begin()+i);
            legal_play_exists = true;
            break;
        }
        ++i;
        pile_of_interest = nullptr;
    }
    if (legal_play_exists == false) {
        discard_pile.push_back(hand[0]);
        cout << "Player" << getPlayer_num() << " discards " << hand[0]->getName() << "." << endl; 
        hand.erase(hand.begin());
    }
}





