#include "Dealer.h"
#include <iostream>
Player::Player (string name){
    handIndx = 0;
    stat.setName(name);
    hand = new string[HAND_SIZE];
}

Player::~Player() {
    delete [] hand;
}

void Player::draw(Dealer *dealer) {
    hand[handIndx++] = dealer->deal();
}

ostream &operator << (ostream &strm, Player *tmp) {
    strm << "Here is your hand: " << endl;
    strm << "First card:  " << tmp->getCard(0) << endl;
    strm << "Second card: " << tmp->getCard(1) << endl;
    if (tmp->getValue(0) == 1 && tmp->getValue(1) != 1) {
        int ace;
        do {
            try {
                strm << "\nYour first card is an Ace. An Ace can either be 1 or"
                     << " 11. Enter 1 or 11 to assign it: ";
                tmp->assignAce(ace);
            }
            catch(Player::WrongAce) {
                strm << "\nERROR: Invalid number entered please try again.\n";
            }
        } while (ace != 1 && ace != 11);
        tmp->setSum(ace + tmp->getValue(1));
        strm << "\nHere is your total: " << tmp->getSum() << endl;
    }
    else if (tmp->getValue(0) != 1 && tmp->getValue(1) == 1) {
        int ace;
        do {
            try {
                strm << "\nYour second card is an Ace. An Ace can either be 1 "
                     << "or 11. Enter 1 or 11 to assign it: ";
                tmp->assignAce(ace);
            }
            catch(Player::WrongAce) {
                strm << "\nERROR: Invalid number entered please try again.\n";
            }
        } while (ace != 1 && ace != 11);
        tmp->setSum(ace + tmp->getValue(0));
        strm << "\nHere is your total: " << tmp->getSum() << endl;
    }
    else if (tmp->getValue(0) == 1 && tmp->getValue(1) == 1) {
        int ace1;
        int ace2;
        do {
            try {
                strm << "\nYour first card is an Ace. An Ace can either be 1 or"
                     << " 11. Enter 1 or 11 to assign it: ";
                tmp->assignAce(ace1);
                strm << "\nYour second card is an Ace. An Ace can either be 1 "
                     << "or 11. Enter 1 or 11 to assign it: ";
                tmp->assignAce(ace2);
            }
            catch(Player::WrongAce) {
                strm << "\nERROR: Invalid number entered please try again.\n";
            }
        } while ((ace2 != 1 && ace2 != 11) && (ace1 != 1 && ace1 != 11));
        tmp->setSum(ace1 + ace2);
        strm << "\nHere is your total: " << tmp->getSum() << endl;
    }
    else {
        tmp->setSum(tmp->getValue(0) + tmp->getValue(1));
        strm << "\nHere is your total: " << tmp->getSum() << endl;
    }
    return strm;
}

int Player::getValue(int indx) const {
    string tmp = hand[indx];
    if (tmp[1] == '0' || tmp[0] == 'J' || tmp[0] == 'Q' || tmp[0] == 'K') 
        return 10;
    else if (tmp[0] == 'A') return 1;
    else return static_cast<int>(tmp[0]) - 48;
}

void Player::assignAce(int &ace) {
    cin >> ace;
    if (ace == 1 || ace == 11);
    else throw WrongAce();
}

bool Player::operator > (const Dealer *right) const {
    if (stat.getSum() > right->getSum()) return true;
    else return false;
}

bool Player::operator == (const Player *right) const {
    if (stat.getSum() == right->getSum()) return true;
    else return false;
}
