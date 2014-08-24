/*
 * File:   main.cpp
 * Author: CHRISHOME
 *
 * BYTELAND GOLD COIN Algorithm:
 * In Byteland they have a very strange monetary system.
 * Each Bytelandian gold coin has an integer number written on it. A coin n
 * can be exchanged in a bank into three coins: n/2, n/3 and n/4.
 * But these numbers are all rounded down (the banks have to make a profit).
 * You can also sell Bytelandian coins for American dollars. The exchange
 * rate is 1:1. But you can not buy Bytelandian coins.
 * You have one gold coin. What is the maximum amount of American dollars
 * you can get for it?
 *
 * Input:
 * The input will contain several test cases (not more than 10). Each
 * test case is a single line with a number n, 0 <= n <= 1 000 000 000.
 * It is the number written on your coin.
 * Output:

 * For each test case output a single line, containing the maximum amount
 * of American dollars you can make.
 * Example

 * Input:
 * 12
 * 2
 * Output:
 * 13
 * 2
 */

#include <iostream>
#include <map>
#include <cstdio>

using namespace std;

map <long long, long long> bc;    //bytecoin map.

//Returns the maximum value of a and b.
long long int max(long long int a, long long int b)
{
    return (a>b ? a : b);
}

//Recursive function
long long int assignCoins(long long int n)
{
    //Ensure map location is cleared, else return n.
    if (bc[n] != 0) {
        return bc[n];
    }

    if (bc[n] == 0) {
        bc[n/2] = assignCoins(n / 2);
        bc[n/3] = assignCoins(n / 3);
        bc[n/4] = assignCoins(n / 4);
    }

    bc[n] = max(n, bc[n/2] + bc[n/3] + bc[n/4]);
    return bc[n];
}

int main()
{
    long long int n, i, ans;

    for (i = 0; i < 12; i++) { bc[i] = i; }     //Assign initial values to map.

    while (scanf("%lld", &n) != EOF) {           //Check stdin until EOF (-1).
        if (n == 0) { printf("%d\n", 0); }
        else {
            ans = assignCoins(n);
            printf("%lld\n", ans);
        }

    }

    return 0;
}


