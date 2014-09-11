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
    int value;    //The card's numerical value
    char* type;  //The card's type (1, 2.. Ace).
    char* suit;  //The card's suit

    public:
        void generate() {
        //
           value = rand() % 11 + 1; //rand from 1 to 11.
    //        cout << "type: " << type << "\n";
            if (value == 10) {
                int face = rand() % 4;  //rand from 0 to 2.
                switch(face) {
                    case 0:
                        type = "Jack";
                        break;
                    case 1:
                        type = "Queen";
                        break;
                    case 2: 
                        type = "King";
                        break;
                    case 3:
                        type = "Ten";
                        break;
                    default:
                        cout << "Error";
                }
            
     //       cout << "suit: " << suit << "\n";         
            }
            else if (value == 11) {
                type = "Ace";
            }
            else {
                switch(value) {
                    case 1:
                        type = "One";
                        break;
                    case 2:
                        type = "Two";
                        break;
                    case 3:
                        type = "Three";
                        break;
                    case 4:
                        type = "Four";
                        break;
                    case 5:
                        type = "Five";
                        break;
                    case 6:
                        type = "Six";
                        break;
                    case 7:
                        type = "Seven";
                        break;
                    case 8:
                        type = "Eight";
                        break;
                    case 9:
                        type = "Nine";
                        break;
                    default:
                        cout << "Error";
                }
            }
        }
        
        int getValue() {
            return value;
        }
        char* getType() {
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
    cout << "value1: " << c1.getValue() << "\n";
    c2.showCard();
    cout << "value2: " << c2.getValue() << "\n";

    cout << "Please Enter an option: (H)it, (S)tay, (Q)uit...\n";
    return 0;
}

