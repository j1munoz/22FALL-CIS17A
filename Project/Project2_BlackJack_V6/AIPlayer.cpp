#include "AIPlayer.h"

AIPlayer::AIPlayer(string name) {
    handIndx = 0;
    stat.setName(name);
    hand = new string[HAND_SIZE];
}

AIPlayer::AIPlayer() {
    handIndx = 0;
    stat.setName("Bob");
    hand = new string[HAND_SIZE];
}
