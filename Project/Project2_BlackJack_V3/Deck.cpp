#include "Deck.h"
#include <algorithm>
#include <iostream>
using namespace std;
int Deck::indx = 0;
Deck::Deck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards.push_back(face[j] + suit[i]);
        }
    }
    
}

void Deck::shuffleDeck() {
    srand(time(0));
    random_shuffle(cards.begin(), cards.end());
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 52; j++) {
            int temp = rand() % 52;
            swap(cards[i], cards[temp]);
        }
    }
}
