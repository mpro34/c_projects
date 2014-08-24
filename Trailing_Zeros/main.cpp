/* 
 * File:   main.cpp
 * Author: CHRIS
 * PROBLEM STATEMENT
 * The problem is so called "Traveling Salesman Problem" and it is very hard to solve. If we have N BTSes to be visited, we can visit them in any order, giving us N! 
 * possibilities to examine. The function expressing that number is called factorial and can be computed as a product
 * 1.2.3.4....N. The number is very high even for a relatively small N.
 * The programmers understood they had no chance to solve the problem. But because they have already received the research grant from the government, they needed to
 * continue with their studies and produce at least some results. So they started to study behavior of the factorial function.
 * For example, they defined the function Z. For any positive integer N, Z(N) is the number of zeros at the end of the decimal form of number N!. They noticed that this
 * function never decreases. If we have two numbers N1<N2, then Z(N1) <= Z(N2). It is because we can never "lose" any
 * trailing zero by multiplying by any positive number. We can only get new and new zeros. The function Z is very interesting, so we need a computer program that can determine its value efficiently.
 * Input:
 * There is a single positive integer T on the first line of input (equal to about 100000). It stands for the number of numbers to follow. Then there are T lines, 
 * each containing exactly one positive integer number N, 1 <= N <= 1000000000.
 * Output:
 * For every number N, output a single line containing the single non-negative integer Z(N).
 * Example:

Sample Input:
6
3
60
100
1024
23456
8735373
Sample Output:
0
14
24
253
5861
2183837

 */

#include <cstdlib>
#include <iostream>
using namespace std;

/*Determines the zeros by dividing N by multiples of 5 and adding to zeros.
 * Utilizes function numFives to determine the resulting zeros.
 * Adds results to rArray to be printed out later.
 */
int main() {
    long int T, N, Z, Fives, Result = 0;
    int* rArray = new int[999999]; 

    cin >> T;
    if (T <= 100000) {
        for (int i = 0; i < T; i++) {
            Z = 0;
            Fives = 5;
            cin >> N; 
            if (N >= 1 && N <= 1000000000) {                                  
                while (Fives > 1) {
                    Z += N / Fives;
                    Fives *= 5;
                }
                rArray[i] = Z;
            }
        }
    }
//Prints out each resulting zeros value per input by users from within rArray.
    for (int j=0; j < T; j++) { 
        cout << rArray[j] << endl;
    }
        
    return 0;
}


    