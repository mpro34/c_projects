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
    int choice = 0;
    while (choice != 3) {
        srand(time(NULL));  //To generate unique cards.
        cout << "Welcome to BlackJack!\n";
        cout << "Here are your cards: \n";
        Card c1;
        Card c2;
        c1.generate();
        c2.generate();
        cout << "\n";  //generate new line
        c1.showCard();
        c2.showCard();
        cout << "\n";   //generate new line
        cout << "Please Enter an option: (1)Hit, (2)Stay, (3)Quit...\n"; 
        cin >> choice;
    }
};

/*
 * 
 */
int main(int argc, char** argv) {
    gameStart();

    return 0;
}

