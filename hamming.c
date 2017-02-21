#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int hammingDistance(int x, int y);

int main()
{
    printf("%d\n", hammingDistance(93,73));
    return 0;
}


int hammingDistance(int x, int y) {
    /*First must convert x and y to binary */
    int buffx[50], buffy[50], i=1, j=1, found_from_start=0, found_from_end=0, hamming=0;
    int copyx = x;
    int copyy = y;

    /* Convert x and y to binary */
    while (copyx != 0) {
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

    /* Search from end to start */
    for (int c=i-1; c > 0; c--) {
        if (buffx[c] != buffy[c]) {
          found_from_end = c;
          break;                    //Get out as soon as a diff
        }
    }
    /* Search from start to end */
    for (int c=0; c < i; c++) {
        if (buffx[c] != buffy[c]) {
          found_from_start = c;
          break;                     //Get out as soon as a diff
        }
    }

    printf("start: %d, end %d\n", found_from_start, found_from_end);
    /* Calculate hamming distance */
    if (found_from_start >= found_from_end) {
      hamming = found_from_start - found_from_end;
    } else {
      hamming = found_from_end - found_from_start;
    }

    return hamming;
};
