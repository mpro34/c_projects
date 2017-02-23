#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int32_t complement(int32_t x);

int main()
{
    int x = 5;
    int y = 2;
    float dx[5] = {0.55, 0.45, 0.353, 0.4235};
    float dy = 2;
    fprintf(stdout, "int: %i, float: %f\n", (x/y), (dx[0]*dy));

    printf("Answer: %d\n", complement(2));
    return 0;
}


int32_t complement(int32_t x) {
    /*First must convert x and y to binary */
    int32_t buffx[50], i=1, comp=0, mask=0, n=0, remainder=0, dec=0;
    int copyx = x;

    buffx[i] = 0;
    /* Convert decimal x to binary */
    while (copyx != 0) {
        buffx[i++] = copyx % 2;
        copyx = copyx / 2;
    }
    /* Converting binary array to 32-bit binary */ 
    for (int j=1; j < i; j++) {
        comp = 10 * comp + buffx[j];
    }
    /* Create mask */
    for (int k=0; k < i-1; k++) {
        mask = 10 * mask + 1;  //'1' is the mask value. If set to 2, the mask would be 222 or similar.
    }
    /* Apply mask */
    comp ^= mask;

    /* Convert binary to decimal */    
    while (comp!=0) {
        remainder = comp%10;
        comp /= 10;
        dec += remainder*pow(2,n);
        ++n;
    }
    return dec;
};
