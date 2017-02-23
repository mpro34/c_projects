#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int hammingDistance(int x, int y);

int main()
{
    //printf("%d\n", hammingDistance(93,73));
    printf("%d\n", hammingDistance(1,4));
    return 0;
}


int hammingDistance(int x, int y) {
    /*First must convert x and y to binary */
    int buffx[50], buffy[50], i=1, j=1, hamming=0;
    int copyx = x;
    int copyy = y;

    buffx[i] = 0;
    buffy[j] = 0;
    /* Convert x and y to binary */
    while (copyx != 0) {
        printf("copyx: %d, mod: %d\n", copyx, (copyx % 2));
        buffx[i++] = copyx % 2;
        copyx = copyx / 2;
    }
    while (copyy != 0) {
        buffy[j++] = copyy % 2;
        copyy = copyy / 2;
    }
    /* Get minimum value of i or j, such that we can match lengths of copy arrays. */
    if (i >= j) {
      j = i;
    } else {
      i = j;
    }
    for (int p=i; p > 0; p--) {
      printf("x: %d   y: %d\n", buffx[p], buffy[p]);
    }
    /* Search from end to start */
    for (int c=i-1; c > 0; c--) {
        printf("buffx: %d  buffy: %d\n", buffx[c], buffy[c]);
        if (buffx[c] != buffy[c]) {
          hamming++;                    //Increment if bits are different
        }
    }
    return hamming;
};
