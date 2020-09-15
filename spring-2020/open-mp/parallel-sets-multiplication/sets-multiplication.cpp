#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Must be equal to thread count.
// Use directive, not variable since it's a shared resource.
#define SET_POWER 4

const unsigned short int SETS_COUNT = 3;

int main(int argc, char *argv[]) {
    // All sets have equal power = > use matrix representation
    int arr[SETS_COUNT][SET_POWER];

    // Fill matrix with random values
    for (unsigned int i = 0; i < SETS_COUNT; i++) {
        for (unsigned int j = 0; j < SET_POWER; j++) {
            // get random value from range [0-9]
            const unsigned int randValue = (rand() % 10) + 1;
            arr[i][j] = randValue;
            // print current value of the matrix
            printf(" %d", arr[i][j]);
        }
        // -- rows delimiter
        printf("\n");
    }
    // -- matrix delimiter
    printf("\n");

    // rowsCount = all possible ordered pairs of elements of the original sets => ...
    // ... => setPower^$(setCount)
    const unsigned int rowsCount = pow(SET_POWER, SETS_COUNT);
    const unsigned int colCount = SETS_COUNT;
    int setsMultiplication[rowsCount][colCount];

    int colIdx, rowsIdx, resRowCount, n, m;
#pragma omp parallel for shared(res, arr, rnum, cnum) \
        private(i, j, k, n, m) \
        num_threads(SET_POWER)
    for (colIdx = 0; colIdx < colCount; colIdx++) {
        resRowCount = pow(SET_POWER, colIdx);
        // Calculating coordinate components
        for (rowsIdx = 0; rowsIdx < SET_POWER; rowsIdx++) {
            for (m = 0; m < resRowCount; m++) {
                for (n = 0; n < rowsCount; n += pow(SET_POWER, colIdx + 1)) {
                    const unsigned int resRowIdx = resRowCount*rowsIdx + m + n;
                    setsMultiplication[resRowIdx][colIdx] = arr[colIdx][rowsIdx];
                }
            }
        }
    }

    // print-out the result: setsMultiplication. dim(setsMultiplication)=[rowsCount][colCount]
    for (unsigned int i = 0; i < rowsCount; i++) {
        for (unsigned int j = 0; j < colCount; j++) {
            printf(" %d", setsMultiplication[i][j]);
        }

        // print EOL
        printf("\n");
    }
    return EXIT_SUCCESS;
}


