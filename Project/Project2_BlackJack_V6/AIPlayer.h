#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "Dealer.h"

class AIPlayer : public Player {
    public:
        AIPlayer();
        AIPlayer(string name);
        void destroy() {delete [] hand;}
};

#endif /* AIPLAYER_H */
