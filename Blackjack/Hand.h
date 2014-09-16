/* 
 * File:   Hand.h
 * Author: CHRISHOME
 *
 * Created on September 14, 2014, 9:00 AM
 * Implements a Hand class which keeps track of an array of cards up to 21.
 */

#ifndef HAND_H
#define	HAND_H
#include <iostream>
#include <cstdlib>
#include "Card.h"

class Hand {
    Card myHand[21];
    int size;

    public:
    //Add standard to cards to Hand array.
        Hand(Card c1, Card c2) {
            myHand[0] = c1;
            myHand[1] = c2;
            size = 2;
        }
    //Add card to Hand array of cards.
        void hit() {
            Card c;
            c.generate();
            myHand[size] = c;
            size++;
        }

        Card &operator[](int i) {
            if (i > size) {
                cout << "Index out of bounds!" << endl;
                return myHand[0];
            }
            return myHand[i];
        }

        void hGenerate() {
            for (int i=0; i < size; ++i) {
                myHand[i].generate();
            }
        }

        void getHValue() {
            for (int i=0; i < size; ++i) {
                cout << myHand[i].getValue() << endl;
            }
        }
};

#endif	/* HAND_H */

