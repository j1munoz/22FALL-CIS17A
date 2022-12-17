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
