#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define CONN_POINTS 2

const int TRANSF_VALUES[N] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
const unsigned short int MSG_TAG = 0;

int main(int argc, char* argv[]) {

    int processNum, processCount;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processNum);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    char dataReceived[CONN_POINTS];

    const bool shouldBroadcast = (processNum == 0);
    if (!shouldBroadcast) {
        // receive broadcast data
        MPI_Recv(&dataReceived, CONN_POINTS, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        // Array broadcast
        for (unsigned int procIdx = 0; procIdx < N; procIdx++) {
            MPI_Send(&TRANSF_VALUES[procIdx * CONN_POINTS],
                     DATA_POINTS,
                     MPI_INT,
                     procIdx + 1,
                     MSG_TAG,
                     MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

