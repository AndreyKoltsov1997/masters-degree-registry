#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define RECEIVING_ELEMS_COUNT 100

const int TRANF_VALUES[N][N] = {
        { 2, 4, 6 },
        { 8, 10, 12 },
        { 14, 16, 18 }
};

int main(int argc, char *argv[]) {
    int processNum = 0;
    int processCount = 0;
    char receivingBuffer[RECEIVING_ELEMS_COUNT];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processNum);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    int bucketSize = (N*N)%processCount;

    int *sendCounts = malloc(sizeof(int)*processCount);
    int *bucketOffset = malloc(sizeof(int)*processCount);

    int elemToProc = 0;
    for (unsigned int i = 0; i < processCount; i++) {
        sendCounts[i] = (N*N)/processCount;
        if (bucketSize > 0) {
            sendCounts[i]++;
            bucketSize--;
        }
        bucketOffset[i] = elemToProc;
        elemToProc += sendCounts[i];
    }

    MPI_Scatterv(&TRANF_VALUES, // start address of the send buffer
                 // elements broadcasting to each process
                 sendCounts,
                 // offset from the buffer for i-th process
                 bucketOffset,
                 // data type
                 MPI_CHAR,
                 // address of receiving buffer
                 &receivingBuffer,
                 // amount of expected elements
                 RECEIVING_ELEMS_COUNT,
                 // type of receiving elements
                 MPI_CHAR,
                 // sender process ID
                 0,
                 // communicator
                 MPI_COMM_WORLD);

    MPI_Finalize();
    free(bucketOffset);
    free(bucketOffset);
    return EXIT_SUCCESS;
}

