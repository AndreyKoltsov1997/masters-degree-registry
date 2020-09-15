#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Given sequence: {a0…an–1}.
// The program must perform the following operations againt the sequence:  a0-а1+a2-а3+a4-а5+...

// if threads count < threshold => get system's max thread count, otherwise ...
// ... use threshold value.
const unsigned short int THREADS_THRESHOLD = 4;

int main(int argc, char *argv[]) {
    const int sequence[] = { 17, 5, 2, 4, 5, 1, 5, 1 };
    int seqEntries = sizeof(sequence)/sizeof(int);
    int evenNumbersSum = 0;
    int oddNumbersSum = 0;

    const unsigned int maxThreadCount = omp_get_max_threads();
    const bool useMaxThreads = (maxThreadCount < THREADS_THRESHOLD);
    const unsigned int targetThreadCount = useMaxThreads ? maxThreadCount : THREADS_THRESHOLD;
    omp_set_num_threads(targetThreadCount);


#pragma omp parallel \
    shared(sequence) \
    reduction(+ : evenNumbersSum) \
    reduction(- : oddNumbersSum)
    {
#pragma omp for
        // Given formula: a0-а1+a2-а3+a4-а5+...
        // We'd use first even number as a loop-baseline. Even-indexed numbers'd be summarized, ...
        // .. odd-indexed - subtracted.
        for (unsigned int evenNumIdx = 0; evenNumIdx < seqEntries; evenNumIdx = evenNumIdx + 2) {
            //
            evenNumbersSum += sequence[evenNumIdx];
            if (seqEntries > evenNumIdx + 1) {
                oddNumbersSum += sequence[evenNumIdx + 1];
            }
            printf("Thread %d / %d : odd numbers count: %d, even numbers count: %d, baseline index = %d\n",
                   omp_get_thread_num(),
                   omp_get_num_threads(),
                   evenNumbersSum,
                   oddNumbersSum,
                   evenNumIdx);
        }
    }
    // subtract total count of odd numbers from even numbers
    printf("Result: %d \n", evenNumbersSum - oddNumbersSum);
    return 0;
}

