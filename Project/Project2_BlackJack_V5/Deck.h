#ifndef DECK_H
#define DECK_H
#include <vector>
#include <string>
using namespace std;

class Deck {
    private:
        static int indx;
        string suit[4] = {" of Spades", " of Clubs", " of Diamonds", 
                           " of Hearts"};
        string face[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", 
                           "J", "Q", "K"};
        vector<string> cards;
    public:
        Deck();
        void reset() {indx = 0;}
        void shuffleDeck();
        string getCard() {return cards[indx++];}
};

#endif /* DECK_H */
