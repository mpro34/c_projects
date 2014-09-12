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

