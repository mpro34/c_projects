/* 
 * File:   Money.h
 * Author: CHRISHOME
 *
 * Created on September 14, 2014, 8:50 AM
 */

#ifndef MONEY_H
#define	MONEY_H
#include <iostream>
#include <cstdlib>

class Money {
    int amount;

    public:
        Money(int w) {
            amount = w;
        }
        int getAMT() {
            return amount;
        }
        void win() {
            amount++;
        }
        void lose() {
            amount--;
        }
        void showMoney() {
            cout << "You have: " << amount << "\n";
        }
};


#endif	/* MONEY_H */

