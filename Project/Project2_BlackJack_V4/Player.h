#ifndef PLAYER_H
#define PLAYER_H
#include "Stats.h"
class Dealer;
class Player;
ostream &operator << (ostream &strm, Player *tmp);
class Player {
    protected:
        const int HAND_SIZE = 8;
        short handIndx;
        string *hand;
        Stats stat;
    public:
        Player() {handIndx = 0;}
        Player(string name);
        class WrongAce{};
        virtual ~Player();
        void draw(Dealer *dealer);
        void setSum(int value) {stat.setSum(value);}
        void assignAce(int &ace);
        int getSum() const {return stat.getSum();}
        int getValue(int indx) const;
        string getCard(int i) const {return hand[i];}
        string getName() const {return stat.getName();}
        bool operator > (const Dealer *right) const;
        bool operator == (const Player *right) const;
};

#endif /* PLAYER_H */
