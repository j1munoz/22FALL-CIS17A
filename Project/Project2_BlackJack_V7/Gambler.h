#ifndef GAMBLER_H
#define GAMBLER_H
#include "Money.h"
#include <string>

template <class T>
class Gambler : public Money<T> {
    private:
        string name;
        T bet;
        char choice;
    public:
        Gambler(string name);
        void setChoice(char guess) {choice = guess;}
        void setBet(T bet) {this->bet = bet;}
        char getChoice() const {return choice;}
        T getMoney() const {return Money<T>::money;}
        string getName() const {return name;}
        void winBet() {Money<T>::money += bet;}
        void loseBet() {Money<T>::money -= bet;}
};

template <class T>
Gambler<T>::Gambler(string name) : Money<T>() {
    this->name = name;
}

#endif /* GAMBLER_H */
