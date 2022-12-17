#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include "Dealer.h"     // Includes Dealer class and Player class
#include "AIPlayer.h"   // Includes AIPlayer class
#include "Gambler.h"    // Includes Gambler class
using namespace std;

/*******************************************************************************
 * rules Function - This function will display the rules of the game. (called 
 * in menu option 2)
 ******************************************************************************/
void rules();

/*******************************************************************************
 * AI Function - This function will generate an AI and have it play a game of 
 * BlackJack. (called in menu options 3 and 4)
 ******************************************************************************/
AIPlayer *AI(AIPlayer *ai, Dealer *dealer);

/*******************************************************************************
 * getPlayerInfo Function - This function will get each player's information
 * (called for menu option 1)
 ******************************************************************************/
Player **getPlayerInfo(short &numPlayers);

/*******************************************************************************
 * userHand Function - This function will get the hand of each player
 * (called in menu option 1)
 ******************************************************************************/
void userHand(Player **players, short numPlayers, Dealer *dealer);

/*******************************************************************************
 * dealerTurn Function - This function will proceed with the dealer's turn
 * (called in menu option 1, 3, and 4)
 ******************************************************************************/
void dealerTurn(Dealer *dealer);

/*******************************************************************************
 * results Function - This function will output the results of the game between
 * the players and dealer. (called in menu option 1)
 ******************************************************************************/
void results(Player **players, Dealer *dealer, short numPlayers);

/*******************************************************************************
 * resultsAI Function - This function will output the results of the game 
 * between the AI and dealer. (called in menu options 3 and 4)
 ******************************************************************************/
void resultsAI(AIPlayer *ai, Dealer *dealer);

/*******************************************************************************
 * betResults Function - This function will output the bet results of each 
 * player. (called in menu option 4)
 ******************************************************************************/
void betResults(Gambler<float> **person, AIPlayer *ai, Dealer *dealer, 
                short gamblers);

/*******************************************************************************
 * getGamblerInfo Function - This function will get the information of each 
 * person to proceed with the betting. (called in menu option 4)
 ******************************************************************************/
Gambler<float> **getGamblerInfo(short &gamblers);

/*******************************************************************************
 * bet Function - This function will get the bet of each person
 * (called in menu option 4)
 ******************************************************************************/
void bet(Gambler<float> **person, short gamblers);

/*******************************************************************************
 * finalScores Function - This function will output the final scores of the 
 * betting (called in menu option 4)
 ******************************************************************************/
void finalScores(Gambler<float> **person, short gamblers);

/*******************************************************************************
 * playAgain Function - This function will allow the user to play another game
 * (called in menu option 4)
 ******************************************************************************/
bool playAgain(Gambler<float> **person, short gamblers);

/*******************************************************************************
 * destroy Functions - These functions will de-allocate any memory
 ******************************************************************************/
void destroy(Player **players, short numPlayers, Dealer *dealer);
void destroyAI(AIPlayer *ai, Dealer *dealer);
void destroyGam(Gambler<float> **person, short gamblers);

int main() {
    // Declare Variables
    char menu;          // Menu choices
    
    // Display Menu
    do {
        cout << "\t-----------------" << endl;
        cout << "\t    BlackJack" << endl;
        cout << "\t1. Play" << endl;
        cout << "\t2. Rules" << endl;
        cout << "\t3. Simulate a game" << endl;
        cout << "\t4. Bet on AI" << endl;
        cout << "\t5. Quit" << endl;
        cout << "\t-----------------" << endl;
        cout << "Enter your choice here: ";
        cin >> menu;
        
        // Get the menu choices
        switch(menu) {
            case '1': {
                // Declare Variables
                Dealer *dealer;      // The dealer
                Player **players;    // The players
                short numPlayers;    // Number of players
                
                // Initialize Variables
                players = getPlayerInfo(numPlayers);
                dealer = new Dealer;
                
                // Get user's cards
                userHand(players, numPlayers, dealer);
                
                // Get dealer's hand
                dealerTurn(dealer);
                
                // Get the results of the game
                results(players, dealer, numPlayers);
                
                // De-allocate memory
                destroy(players, numPlayers, dealer);
            }
                break;
            case '2':
                // Output the rules of the game
                rules();
                break;
            case '3': {
                // Declare Variables
                AIPlayer *ai;       // The AI to simulate a game
                Dealer *dealer;     // The dealer
                
                // Initialize Variables
                dealer = new Dealer;
                
                // Get the AI's cards
                ai = AI(ai, dealer);
                
                // Get the Dealer's cards
                dealerTurn(dealer);
                
                // Get the results of the game
                resultsAI(ai, dealer);
                
                // De-allocate memory
                destroyAI(ai, dealer);
            }
                break;
            case '4': {
                // Declare Variables
                Gambler<float> **person; // The people that will be betting
                short gamblers;          // The amount of people gambling   
                
                // Initialize Variables
                person = getGamblerInfo(gamblers);
                
                // Have the players place their bets
                do {
                    // Declare Variables
                    AIPlayer *ai;           // The AI to simulate the game
                    Dealer *dealer;         // The dealer
                    
                    // Initialize Variables
                    dealer = new Dealer;
                    
                    // Get the player's bets
                    bet(person, gamblers);

                    // Get the AI's cards
                    ai = AI(ai, dealer);

                    // Get the dealer's cards
                    dealerTurn(dealer);

                    // Get the results of the game
                    resultsAI(ai, dealer);

                    // Get results of the bets
                    betResults(person, ai, dealer, gamblers);

                    // Delete AI and Dealer
                    destroyAI(ai, dealer);
                    
                } while(playAgain(person, gamblers));
                
                // Show final totals
                finalScores(person, gamblers);
                
                // Delete Gamblers
                destroyGam(person, gamblers);
            }
                break;
            default:
                if (menu != '5')
                    cout << "ERROR: Invalid choice has been entered, please try"
                         << " again." << endl;
        }
    } while (menu != '5');
    cout << "\n\t*****Thanks for Playing*****\n" << endl;
    
    return 0;
}

/*******************************************************************************
 * rules Function - This function will display the rules of the game. (called 
 * in menu option 2)
 ******************************************************************************/
void rules() {
    cout << "Hi and welcome to BlackJack!" << endl;
    cout << "Here are the rules to this version of BlackJack." << endl;
    cout << "1. You will be asked to enter the amount of players that will play"
         << ". The minimum amount is 1 and the max amount is 4 players." <<endl;
    cout << "2. Each player will be asked to enter their name." << endl;
    cout << "3. Each player is given two cards from the beginning." << endl;
    cout << "4a. An Ace is either a 1 or 11, depending on your choice." << endl;
    cout << "4b. If you happen to draw an Ace, you will be asked to assign it "
         << "to either 1 or 11." << endl;
    cout << "4c. If you enter an invalid number, you will be asked to try again"
         << "." << endl;
    cout << "5a. After getting your two cards, you will be asked to either draw"
         << " a new card, or stand (end your turn)." << endl;
    cout << "5b. If you want to draw, you will enter '1'." << endl;
    cout << "5c. If you want to stand, you will enter '2'." << endl;
    cout << "\nWINNING CONDITIONS (SINGLE PLAYER)" << endl;
    cout << "1. If you have total that is higher than the dealer and your total"
         << " is less than or equal to 21, you win the game." << endl;
    cout << "2. If you have a total that is less than or equal to 21 and the "
         << "dealer is bust (exceed 21), you win the game." << endl;
    cout << "3. If you go bust (exceed 21) and the dealer's total is less than "
         << "or equal to 21, the dealer wins the game." << endl;
    cout << "4. If you and the dealer have the exact same total that is less "
         << "or equal to 21, the dealer wins the game." << endl;
    cout << "5. If you go bust (exceed 21) and so does the dealer, the game "
         << "will end in a draw." << endl;
    cout << "\nWINNING CONDITIONS (MULTIPLAYER)" << endl;
    cout << "1. If one player has a higher total that is less than or equal to"
         << " 21 and that total is higher than the rest of the players, and if "
         << "that total is higher than the dealer, that player wins the game\n";
    cout << "2. If the dealer has a better total than everyone else, the dealer"
         << "wins. " << endl;
    cout << "3. If a set of players have the same total that is less than or "
         << "equal to 21, the game will end in a draw." << endl;
    cout << endl;
}

/*******************************************************************************
 * getPlayerInfo Function - This function will get each player's information
 * (called for menu option 1)
 ******************************************************************************/
Player **getPlayerInfo(short &numPlayers) {
    string name;        // Player's name
    Player **players;   // Players
    
    // Get the amount of players that will be playing
    do {
        cout << "\nHow many players will be playing?(1 - 4): ";
        cin >> numPlayers;
    } while(numPlayers < 1 || numPlayers > 4);
    cin.ignore();
    
    // Get the player names
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter player " << i + 1 << "'s name: ";
        getline(cin, name);
        players[i] = new Player(name);
    }
    return players;
}

/*******************************************************************************
 * getGamblerInfo Function - This function will get the information of each 
 * person to proceed with the betting. (called in menu option 4)
 ******************************************************************************/
Gambler<float> **getGamblerInfo(short &gamblers) {
    string name;        // Person's name
    Gambler<float> **person;     // The gamblers
    
    // Get the amount of players that will be playing
    do {
        cout << "\nHow many players will be playing?(1 - 4): ";
        cin >> gamblers;
    } while(gamblers < 1 || gamblers > 4);
    cin.ignore();
    
    // Get the people's names
    person = new Gambler<float>*[gamblers];
    for (int i = 0; i < gamblers; i++) {
        cout << "Enter person " << i + 1 << "'s name: ";
        getline(cin, name);
        person[i] = new Gambler<float>(name);
    }
    cout << "\nEveryone will start with $500.00\n" << endl;
    return person;
}

/*******************************************************************************
 * bet Function - This function will get the bet of each person
 * (called in menu option 4)
 ******************************************************************************/
void bet(Gambler<float> **person, short gamblers) {
    char guess;         // The guess whether the AI wins, draws, or loses
    float betAmount;    // The amount the user wishes to bet
    
    // Get user input for bets
    cout << "\n\t-------------------------------------------------------"<<endl;
    cout << "\tAlright everyone, you will now place your bets." << endl;
    cout << "\tEnter 'W' if you think the AI will win." << endl;
    cout << "\tEnter 'L' if you think the AI will lose." << endl;
    cout << "\tIf you win your bet, you will receive double." << endl;
    cout << "\tIf you lose your bet, you will lose that amount." << endl;
    cout << "\tIf the game ends in a draw, you will not lose your bet.\n";
    cout << "\t-------------------------------------------------------\n"<<endl;
    for (int i = 0; i < gamblers; i++) {
        if (person[i]->getMoney() <= 0) 
            cout << "Sorry " << person[i]->getName() << ", since you have no "
                 << "more funds, you are out.\n" << endl;
        else {
            short tmp = person[i]->getName().length();  // Used for '-' output
            cout << "\t" << person[i]->getName() << "'s turn" << endl;
            cout << '\t';
            for (int i = 0; i < (tmp + 7); i++) cout << "-";
            cout << endl;
            // Get their bet choice
            do {
                cout << "\tEnter your guess here: ";
                cin >> guess;
                if (toupper(guess) != 'W' && toupper(guess) != 'L')
                    cout << "\tERROR: Invalid guess entered, please try again."
                         << endl;
                person[i]->setChoice(toupper(guess));
            } while (toupper(guess) != 'W' && toupper(guess) != 'L');

            // Get their bet amount
            cout << "\tEnter your bet amount here: $";
            cin >> betAmount;
            while (betAmount > person[i]->getMoney() || betAmount <= 0) {
                if (betAmount > person[i]->getMoney())
                    cout << "\tERROR: Insufficient funds to bet with, please "
                         << " try again." << endl;
                else if (betAmount <= 0)
                    cout << "\tERROR: You must place a bet, please try again."
                         << endl;
                cout << "\tEnter your bet amount here: $";
                cin >> betAmount;
            }
            person[i]->setBet(betAmount);
            cout << endl;
        }
    }
}

/*******************************************************************************
 * AI Function - This function will generate an AI and have it play a game of 
 * BlackJack. (called in menu options 3 and 4)
 ******************************************************************************/
AIPlayer *AI(AIPlayer *ai, Dealer *dealer) {
    char choice;        // Allows user to pick the AI's name
    int indx = 1;       // Index of current hand
    char draw;          // Draw card or end turn
    
    // Get AI name if user wants to
    cout << "\nBefore we begin would you like to choose the AI's name? Enter "
         << "'Y' for Yes or 'N' for no: ";
    do {
        cin >> choice;
        if (toupper(choice) != 'Y' && toupper(choice) != 'N')
            cout << "ERROR: Invalid choice entered, please try again." << endl;
    } while(toupper(choice) != 'Y' && toupper(choice) != 'N');
    if (toupper(choice) == 'Y') {
        cin.ignore();
        string name;
        cout << "\nPerfect! Enter the AI's name here: ";
        getline(cin, name);
        ai = new AIPlayer(name);
    }
    else {
        ai = new AIPlayer;
        cout << "Since no name was given, the name of the AI is: " 
             << ai->getName() << endl;
    }
    // Get the AI's hand
    for (int i = 0; i < 2; i++) ai->draw(dealer);
    
    // Output the AI's cards
    cout << "\n\tHere is " << ai->getName() << "'s hand: " << endl; 
    cout << "The first card:  " << ai->getCard(0) << endl;
    cout << "The second card: " << ai->getCard(1) << endl;
    
    // Output total, terminate if/else-if ladder if Ace was drawn
    if (ai->getValue(0) == 1 && ai->getValue(1) != 1) {
        ai->setSum(11 + ai->getValue(1));
        cout << ai->getName() << "'s first card was an Ace and assigns it"
              << " to 11." << endl;
        cout << "\nHere is " << ai->getName() << "'s total: " << ai->getSum()
             << endl;
    }
    else if (ai->getValue(0) != 1 && ai->getValue(1) == 1) {
        ai->setSum(ai->getValue(0) + 11);
        cout << ai->getName() << "'s second card was an Ace and assigns it"
              << " to 11." << endl;
        cout << "\nHere is " << ai->getName() << "'s total: " << ai->getSum()
             << endl;
    }
    else if (ai->getValue(0) == 1 && ai->getValue(1) == 1) {
        ai->setSum(1 + 11);
        cout << ai->getName() << " drew two Aces. He assigns the first one "
             << "to 1 and the other to 11." << endl;
        cout << "\nHere is " << ai->getName() << "'s total: " << ai->getSum()
             << endl;
    }
    else {
        ai->setSum(ai->getValue(0) + ai->getValue(1));
        cout << "\nHere is " << ai->getName() << "'s total: " << ai->getSum()
             << endl;
    }
    
    // Have AI draw if his sum is less than 18
    if (ai->getSum() >= 18) cout << ai->getName() << " stands\n";
    else {
        do {
            cout << "\n\t" << ai->getName() << " draws a card..." << endl;
            ai->draw(dealer);
            cout << ai->getName() << "drew a " << ai->getCard(++indx)
                 << endl;
            if (ai->getValue(indx) == 1) {
                if (11 + ai->getSum() <= 21) {
                    cout << ai->getName() << " drew an Ace and assigns it"
                         << " to 11." << endl;
                    ai->setSum(11);
                    cout << "\nHere is the new total: " 
                         << ai->getSum() << endl;
                }
                else {
                    cout << ai->getName() << " drew an Ace and assigns it"
                         << " to 1." << endl;
                    ai->setSum(1);
                    cout << "\nHere is the new total: " << ai->getSum()
                         << endl;
                }
            }
            else {
                ai->setSum(ai->getValue(indx));
                cout << "\nHere is the new total: " << ai->getSum() << endl;
            }
        } while(ai->getSum() < 18);
    }
    if (ai->getSum() > 21) cout << "\t***" << ai->getName() << " is bust***\n";
    else cout<< "\t***" << ai->getName() << " has ended their turn.***" << endl;
    
    return ai;
}

/*******************************************************************************
 * userHand Function - This function will get the hand of each player
 * (called in menu option 1)
 ******************************************************************************/
void userHand(Player **players, short numPlayers, Dealer *dealer) {
    // Deal cards to player(s)
    for (int i = 0; i < numPlayers; i++)
        for (int j = 0; j < 2; j++)
            players[i]->draw(dealer);
    
    // Have player(s) decide to draw or end their turn
    for (int i = 0; i < numPlayers; i++) {
        int indx = 1;   // Index of current hand
        char draw;      // Draw card or end turn
        
        // Output the player's current cards and total
        cout << "\n\tIt is now " << players[i]->getName() << "'s turn." << endl;
        cout << players[i];

        // Break out if user is over 21 / else keep going
        if (players[i]->getSum() > 21) 
            cout << players[i]->getName() << " is bust." << endl;
        else {
            do {
                cout << "Enter 1 to draw or enter 2 to end your turn: ";
                cin >> draw;
            } while(draw != '1' && draw != '2');
            if (draw == '2') 
                cout << players[i]->getName() << "'s turn has ended.\n";
            else {
                do {
                    indx++;
                    players[i]->draw(dealer);
                    cout << "\nYour card drawn was a: "
                         << players[i]->getCard(indx) << endl;
                    if (players[i]->getValue(indx) == 1) {
                        int ace;
                        do {
                            try {
                                cout << "Your card drawn was an Ace. An Ace can"
                                     << " can either be 1 or 11. Enter 1 or 11"
                                     << " to assign it: ";
                                players[i]->assignAce(ace);
                                players[i]->setSum(ace);
                            }
                            catch(Player::WrongAce) {
                                cout << "ERROR: An invalid value was entered, "
                                     << "please try again." << endl;
                            }
                        } while (ace != 1 && ace != 11);
                    }
                    else players[i]->setSum(players[i]->getValue(indx));
                    cout << "Here is " << players[i]->getName() << "'s new sum"
                         << ": " << players[i]->getSum() << endl;
                    if (players[i]->getSum() > 21) {
                        cout << players[i]->getName() << " is bust." << endl;
                        draw = '2';
                    }
                    else {
                        do {
                            cout << "Enter 1 to draw or enter 2 to end your "
                                 << "turn: ";
                            cin >> draw;
                        } while(draw != '1' && draw != '2');
                    }
                } while (draw != '2');
            }
        }
    }
}

/*******************************************************************************
 * dealerTurn Function - This function will proceed with the dealer's turn
 * (called in menu option 1, 3, and 4)
 ******************************************************************************/
void dealerTurn(Dealer *dealer) {
    int indx = 1;   // Index for card values
    cout << "\n\tNow it's " << dealer->getName() << "'s turn, our dealer.\n";
    cout << dealer->getName() << " draws his first two cards..." << endl;
    for (int i = 0; i < 2; i++) dealer->draw(dealer);
    cout << "Here are his first two cards: \n" << endl;
    cout << "First card:  " << dealer->getCard(0) << endl;
    cout << "Second card: " << dealer->getCard(1) << endl << endl;
    
    // Output total, terminate if/else-if ladder if Ace was drawn
    if (dealer->getValue(0) == 1 && dealer->getValue(1) != 1) {
        dealer->setSum(11 + dealer->getValue(1));
        cout << dealer->getName() << "'s first card was an Ace and assigns it"
              << " to 11." << endl;
        cout << "Here is his total: " << dealer->getSum() << endl;
    }
    else if (dealer->getValue(0) != 1 && dealer->getValue(1) == 1) {
        dealer->setSum(dealer->getValue(0) + 11);
        cout << dealer->getName() << "'s second card was an Ace and assigns it"
              << " to 11." << endl;
        cout << "Here is his total: " << dealer->getSum() << endl;
    }
    else if (dealer->getValue(0) == 1 && dealer->getValue(1) == 1) {
        dealer->setSum(1 + 11);
        cout << dealer->getName() << " drew two Aces. He assigns the first one "
             << "to 1 and the other to 11." << endl;
        cout << "Here is his total: " << dealer->getSum() << endl;
    }
    else {
        dealer->setSum(dealer->getValue(0) + dealer->getValue(1));
        cout << "Here is his total: " << dealer->getSum() << endl;
    }
    
    // Have dealer draw if his sum is less than 18
    if (dealer->getSum() >= 18) cout << dealer->getName() << " stands\n";
    else {
        do {
            cout << "\t\n" << dealer->getName() << " draws a card..." << endl;
            dealer->draw(dealer);
            cout << dealer->getName() << "drew a " << dealer->getCard(++indx)
                 << endl;
            if (dealer->getValue(indx) == 1) {
                if (11 + dealer->getSum() <= 21) {
                    cout << dealer->getName() << " drew an Ace and assigns it"
                         << " to 11." << endl;
                    dealer->setSum(11);
                    cout << "\nHere is his new total: " 
                         << dealer->getSum() << endl;
                }
                else {
                    cout << dealer->getName() << " drew an Ace and assigns it"
                         << " to 1." << endl;
                    dealer->setSum(1);
                    cout << "\nHere is his new total: " << dealer->getSum()
                         << endl;
                }
            }
            else {
                dealer->setSum(dealer->getValue(indx));
                cout << "\nHere is his new total: " << dealer->getSum() << endl;
            }
        } while(dealer->getSum() < 18);
    }
    if (dealer->getSum() > 21)cout<<"\t***"<<dealer->getName()<<" is bust***\n";
    else cout << "\t***" << dealer->getName() <<" has ended his turn.***"<<endl;
}

/*******************************************************************************
 * results Function - This function will output the results of the game between
 * the players and dealer. (called in menu option 1)
 ******************************************************************************/
void results(Player **players, Dealer *dealer, short numPlayers) {
    if (numPlayers == 1) {
        if (players[0]->getSum() <= 21 && 
           (dealer->getSum() > 21 || players[0] > dealer)) {
            cout << "\nCongratulations " << players[0]->getName() << ", you win"
                 << "!\n" << endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << players[0]->getName() << "'s total sum: "
                 << players[0]->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
        else if (dealer->getSum() <= 21 && 
                (players[0]->getSum() > 21 || 
                 players[0]->getSum() <= dealer->getSum())) {
            cout << "\nSorry " << players[0]->getName() << " you lose.\n"<<endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << players[0]->getName() << "'s total sum: "
                 << players[0]->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
        else if (players[0]->getSum() > 21 && dealer->getSum() > 21) {
            cout << "\nThe game has ended with a draw, no one wins.\n" << endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << players[0]->getName() << "'s total sum: "
                 << players[0]->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
    }
    else {
        // Declare Variables
        int tmp = players[0]->getSum();     // Used to get the highest
        int winIndx = 0;                    // The index of the highest total
        int dupe = 0;                       // Dupe totals found
        
        // Get the player with the highest total
        for (int i = 1; i < numPlayers; i++) {
            if ((players[i]->getSum() > tmp && players[i]->getSum() <= 21) || 
                (tmp > 21 && players[i]->getSum() <= 21)) {
                tmp = players[i]->getSum();
                winIndx = i;
            } 
        }

        // See if any player has drawn in totals
        for (int i = 0; i < numPlayers; i++) {
            for (int j = 0; j < numPlayers; j++) {
                if (players[i] == players[j] && i != j) dupe++; 
            }
        }
 
        // Output the results
        if (tmp > 21) {     // Terminates if no one has a sum <= 21
            if (dealer->getSum() <= 21) {  // Terminates if dealer total <= 21
                cout << "\nThe winner of this game: " <<dealer->getName()<<endl;
                for (int i = 0; i < numPlayers; i++) {
                    cout << "\nSTATS FOR: " << players[i]->getName() << endl;
                    cout << "----------------" << endl;
                    cout << "Your total was: " << players[i]->getSum() << endl;
                    cout << endl;
                }
                cout << "\nSTATS FOR DEALER: " << dealer->getName() << endl;
                cout << "----------------" << endl;
                cout << "Your total was: " << dealer->getSum() << endl;
            }
            else if (dealer->getSum() > 21) {  // Terminate if dealer total > 21
                cout << "\nThe game has ended in a draw." << endl;
                for (int i = 0; i < numPlayers; i++) {
                    cout << "\nSTATS FOR: " << players[i]->getName() << endl;
                    cout << "----------------" << endl;
                    cout << "Your total was: " << players[i]->getSum() << endl;
                    cout << endl;
                }
                cout << "\nSTATS FOR DEALER: " << dealer->getName() << endl;
                cout << "----------------" << endl;
                cout << "Your total was: " << dealer->getSum() << endl;
            }
        }
        else {          // Terminates if one person has a total <= 21
            if (players[winIndx]->getSum() <= 21 &&  // Terminates if person won
               (dealer->getSum() > 21 || players[winIndx] > dealer)) {
                cout << "\nThe winner of this game is: "
                     << players[winIndx]->getName() << endl;
                for (int i = 0; i < numPlayers; i++) {
                    cout << "\nSTATS FOR: " << players[i]->getName() << endl;
                    cout << "----------------" << endl;
                    cout << "Your total was: " << players[i]->getSum() << endl;
                    cout << endl;
                }
                cout << "\nSTATS FOR DEALER: " << dealer->getName() << endl;
                cout << "----------------" << endl;
                cout << "Your total was: " << dealer->getSum() << endl;
            }
            else if (dealer->getSum() <= 21 &&  // Terminates if person lost
                    (players[winIndx]->getSum() > 21 || 
                     players[winIndx]->getSum() <= dealer->getSum())) {
                cout << "\nThe winner of this game: " <<dealer->getName()<<endl;
                for (int i = 0; i < numPlayers; i++) {
                    cout << "\nSTATS FOR: " << players[i]->getName() << endl;
                    cout << "----------------" << endl;
                    cout << "Your total was: " << players[i]->getSum() << endl;
                    cout << endl;
                }
                cout << "\nSTATS FOR DEALER: " << dealer->getName() << endl;
                cout << "----------------" << endl;
                cout << "Your total was: " << dealer->getSum() << endl;
            }
            else if (players[winIndx]->getSum() > 21 && dealer->getSum() > 21) {
                cout << "\nThe game has ended in a draw." << endl;
                for (int i = 0; i < numPlayers; i++) {
                    cout << "\nSTATS FOR: " << players[i]->getName() << endl;
                    cout << "----------------" << endl;
                    cout << "Your total was: " << players[i]->getSum() << endl;
                    cout << endl;
                }
                cout << "\nSTATS FOR DEALER: " << dealer->getName() << endl;
                cout << "----------------" << endl;
                cout << "Your total was: " << dealer->getSum() << endl;
            } // Terminates if no one has a sum <= 21
        }
    }
    cout << "\n\tTotal games played so far: "<<dealer->getGamesPlayed() << endl;
}

/*******************************************************************************
 * resultsAI Function - This function will output the results of the game 
 * between the AI and dealer. (called in menu options 3 and 4)
 ******************************************************************************/
void resultsAI(AIPlayer *ai, Dealer *dealer) {
    // Terminate if AI won
    if (ai->getSum() <= 21 && 
           (dealer->getSum() > 21 || ai->getSum() > dealer->getSum())) {
            cout << "\nCongratulations " << ai->getName() << ", you win"
                 << "!\n" << endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << ai->getName() << "'s total sum: "
                 << ai->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
    else if (dealer->getSum() <= 21 && // Terminate if AI lost
                (ai->getSum() > 21 || 
                 ai->getSum() <= dealer->getSum())) {
            cout << "\nSorry " << ai->getName() << " you lose.\n"<<endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << ai->getName() << "'s total sum: "
                 << ai->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
    else if (ai->getSum() > 21 && dealer->getSum() > 21) {//Terminate if AI drew
            cout << "\nThe game has ended with a draw, no one wins.\n" << endl;
            cout << "      STATS" << endl;
            cout << "-----------------" << endl;
            cout << ai->getName() << "'s total sum: "
                 << ai->getSum() << endl;
            cout << dealer->getName() << "'s total sum: "
                 << dealer->getSum() << endl;
        }
    cout << endl;
}

/*******************************************************************************
 * betResults Function - This function will output the bet results of each 
 * player. (called in menu option 4)
 ******************************************************************************/
void betResults(Gambler<float> **person, AIPlayer *ai, Dealer *dealer, 
                short gamblers) {
    // Terminate if AI won
    if (ai->getSum() <= 21 && 
       (dealer->getSum() > 21 || ai->getSum() > dealer->getSum())) {
            cout << "Here are the results of the bets." << endl;
            for (int i = 0; i < gamblers; i++) {
                if (person[i]->getChoice() == 'W') {
                    cout << person[i]->getName() << " won." << endl;
                    if (person[i]->getMoney() > 0) person[i]->winBet();
                }
                else {
                    cout << person[i]->getName() << " lost." << endl;
                    if (person[i]->getMoney() > 0) person[i]->loseBet();
                }
                cout << "Here is " << person[i]->getName() << "'s new amount: $"
                     << person[i]->getMoney() << endl;
            }
        }
    else if (dealer->getSum() <= 21 && // Terminate if AI lost
                (ai->getSum() > 21 || 
                 ai->getSum() <= dealer->getSum())) {
            cout << "Here are the results of the bets." << endl;
            for (int i = 0; i < gamblers; i++) {
                if (person[i]->getChoice() == 'L') {
                    cout << person[i]->getName() << " won." << endl;
                    if (person[i]->getMoney() > 0) person[i]->winBet();
                }
                else {
                    cout << person[i]->getName() << " lost." << endl;
                    if (person[i]->getMoney() > 0) person[i]->loseBet();
                }
                cout << "Here is " << person[i]->getName() << "'s new amount: $"
                     << person[i]->getMoney() << endl;
            }
        }
    else if (ai->getSum() > 21 && dealer->getSum() > 21) {//Terminate if AI drew
        cout << "\nThe game has ended in a draw, all player's will not lose "
             << "their bets." << endl;
            for (int i = 0; i < gamblers; i++) {
                cout << "Here is " << person[i]->getName() << "'s new amount: $"
                     << person[i]->getMoney() << endl;
            }
        }
}

/*******************************************************************************
 * finalScores Function - This function will output the final scores of the 
 * betting (called in menu option 4)
 ******************************************************************************/
void finalScores(Gambler<float> **person, short gamblers) {
    short highIndx;     // Index of the person with the longest name
    short width = person[0]->getName().length();  // Formatting purposes
    
    // Search for person with the longest name
    for (int i = 1; i < gamblers; i++) {
        if (person[i]->getName().length() > width) {
            width = person[i]->getName().length();
            highIndx = i;
        } 
    }
    cout << "\nHere are your final scores." << endl;
    cout << "---------------------------" << endl;
    cout << showpoint << fixed << setprecision(2);
    for (int i = 0; i < gamblers; i++) {
        if (i != highIndx)
            cout << "Final total for " << person[i]->getName() << ":" 
                 << setw(width+2-person[i]->getName().length()) << " $" 
                 << person[i]->getMoney() << endl;
        else
            cout << "Final total for " << person[i]->getName() << ": $"
                 << person[i]->getMoney() << endl;
    }
    cout << endl;
}

/*******************************************************************************
 * playAgain Function - This function will allow the user to play another game
 * (called in menu option 4)
 ******************************************************************************/
bool playAgain(Gambler<float> **person, short gamblers) {
    char again;     // Allows user to chose to play again or not
    short zero;     // Checks if all players have $0
    
    // End the game if all players have no more money
    for (int i = 0; i < gamblers; i++) if (person[i]->getMoney() == 0) zero++;
    if (zero == gamblers) {
        cout << "\n\tAll players have no more money, the game will now end.\n";
        return false;
    }
    else {
        cout << "\nWould you like to play another round?" << endl;
        do {
            cout << "Enter 'Y' for yes, enter 'N' for no: ";
            cin >> again;
            if (toupper(again) != 'Y' && toupper(again) != 'N')
                cout << "ERROR: Invalid choice entered, please try again.\n";
        } while(toupper(again) != 'Y' && toupper(again) != 'N');
        if (toupper(again) == 'Y') return true;
        else return false;
    }
}

/*******************************************************************************
 * destroy Functions - These functions will de-allocate any memory
 ******************************************************************************/
void destroy(Player **players, short numPlayers, Dealer *dealer) {
    for (int i = 0; i < numPlayers; i++) delete players[i];
    delete [] players;
    dealer->destroy();
    dealer = NULL;
    delete dealer;
}

void destroyAI(AIPlayer *ai, Dealer *dealer) {
    delete ai;
    dealer->destroy();
    dealer = NULL;
    delete dealer;
}

void destroyGam(Gambler<float> **person, short gamblers){
    for (int i = 0; i < gamblers; i++) delete person[i];
    delete [] person;
}
