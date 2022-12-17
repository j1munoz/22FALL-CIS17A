#include "Dealer.h"
#include <iostream>

int Dealer::gamesPlayed = 0;
Dealer::Dealer() {
    dec = new Deck;
    dec->reset();
    dec->shuffleDeck();
    stat.setName("Jerry");
    handIndx = 0;
    hand = new string[HAND_SIZE];
    gamesPlayed++;
}

void Dealer::destroy() {
    delete [] hand;
    delete dec;
}
