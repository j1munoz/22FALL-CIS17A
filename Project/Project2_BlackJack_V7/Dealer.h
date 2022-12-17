#ifndef DEALER_H
#define DEALER_H
#include "Player.h"
#include "Deck.h"
#include <string>

class Dealer : public Player {
    private:
        Deck *dec;
        static int gamesPlayed;
    public:
        Dealer();
        void destroy();
        string deal() {return dec->getCard();}
        void assignAce(int indx);
        int getGamesPlayed() const {return gamesPlayed;}
};

#endif /* DEALER_H */
