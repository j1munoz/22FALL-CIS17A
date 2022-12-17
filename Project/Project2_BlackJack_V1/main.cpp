#include <iostream>
#include "Dealer.h"     // Includes Dealer class and Player class
using namespace std;

/*******************************************************************************
 * rules Function - This function will display the rules of the game. (called 
 * in menu option 2)
 ******************************************************************************/
void rules();

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
 ******************************************************************************/
void dealerTurn(Dealer *dealer);

/*******************************************************************************
 * results Function - This function will output the results of the game between
 * the players and dealer. (called in menu option 1)
 ******************************************************************************/
void results(Player **players, Dealer *dealer, short numPlayers);

/*******************************************************************************
 * destroy Functions - These functions will de-allocate any memory
 ******************************************************************************/
void destroy(Player **players, short numPlayers, Dealer *dealer);

int main () {
    // Declare Variables
    char menu;          // Menu choices
    
    // Display Menu
    do {
        cout << "\t-----------------" << endl;
        cout << "\t    BlackJack" << endl;
        cout << "\t1. Play" << endl;
        cout << "\t2. Rules" << endl;
        cout << "\t3. Search game data" << endl;
        cout << "\t4. Quit" << endl;
        cout << "\t-----------------" << endl;
        cout << "Enter your choice here: ";
        cin >> menu;
        
        // Get the menu choices
        switch(menu) {
            case '1': {
            }
                break;
            case '2':
                // Output the rules of the game
                rules();
                break;
            default:
                if (menu != '4')
                    cout << "ERROR: Invalid choice has been entered, please try"
                         << " again." << endl;
        }
    } while (menu != '4');
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