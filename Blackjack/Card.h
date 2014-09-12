/* 
 * File:   Card.h
 * Author: CHRISHOME
 *
 * Created on September 11, 2014, 5:19 PM
 */

#ifndef CARD_H
#define	CARD_H
#include <iostream>
#include <cstdlib>

using namespace std;

class Card {
    int value;    //The card's numerical value
    char* type;  //The card's type (1, 2.. Ace).
    char* suit;  //The card's suit

    public:
        void generate() {
        //Pick a random value/type for the card(1...Ace).
           value = rand() % 11 + 1; //rand from 1 to 11.
            if (value == 10) {
                int face = rand() % 4;  //rand from 0 to 3.
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
    //Pick a random suit for the card.
            int suitChoice = rand() % 4;  //rand from 0 to 3.
            switch(suitChoice) {
                case 0:
                    suit = "Hearts";
                    break;
                case 1:
                    suit = "Diamonds";
                    break;
                case 2: 
                    suit = "Clubs";
                    break;
                case 3:
                    suit = "Spades";
                    break;
                default:
                    cout << "Error";
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

#endif	/* CARD_H */

