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
#include "Card.h"
#include "Deck.h"

using namespace std; 

void gameStart() {
    srand(time(NULL));  //To generate unique cards.
    cout << "Welcome to BlackJack!\n";
    cout << "Here are your cards: \n";
};

/*
 * 
 */
int main(int argc, char** argv) {
 //   srand(time(NULL));  //To generate unique cards.
 //   cout << "Welcome to BlackJack!\n";
 //   cout << "Here are your cards: \n";
    Card c1;
    Card c2;
    gameStart();
    c1.generate();
    c2.generate();
    cout << "\n";  //generate new line
    c1.showCard();
    c2.showCard();
    cout << "\n";   //generate new line
    cout << "Please Enter an option: (H)it, (S)tay, (Q)uit...\n";
    return 0;
}

