/* 
 * File:   Hand.h
 * Author: CHRISHOME
 *
 * Created on September 14, 2014, 9:00 AM
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
        Hand() {
        }
        Card[] deal() {
        }
    //Add card to Hand array of cards.
        void hit() {
            Card c;
            c.generate();
            
        }
    //Dont add any cards.
        void stay() {
        }
};

#endif	/* HAND_H */

