/* 
 * File:   main.cpp
 * Author: CHRISHOME
 *
 * Created on September 10, 2014, 3:42 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <time.h>
#include <string.h>

using namespace std;

class Card {
    int type;
    char* suit;

    public:
        void generate() {
        //    suit = "Jack";
            type = rand() % 11 + 1; //rand from 1 to 11.
    //        cout << "type: " << type << "\n";
            if (type == 10) {
                int face = rand() % 3;  //rand from 0 to 2.
                switch(face) {
                    case 0:
                        suit = "Jack";
                        break;
                    case 1:
                        suit = "Queen";
                        break;
                    case 2: 
                        suit = "King";
                        break;
                    default:
                        cout << "Error";
                }
            
     //       cout << "suit: " << suit << "\n";         
            }
            else if (type == 11) {
                suit = "Ace";
            }
   
        }
        
        int getType() {
            return type;
        }
        char* getSuit() {
            return suit;
        }

        void showCard() {
            cout << type << " of " << suit << endl;
        }
};
        


class Deck {
    int size[52];
};




/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));  //To generate unique cards.
    cout << "Welcome to BlackJack!\n";
    cout << "Here are your cards: \n";
    Card c1;
    Card c2;
    c1.generate();
    c2.generate();
    c1.showCard();
    c2.showCard();

    cout << "Please Enter an option: (H)it, (S)tay, (Q)uit...\n";
    return 0;
}

