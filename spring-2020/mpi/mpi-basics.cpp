#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ACCOUNTANT_NUM 10

const unsigned int PROCESS_IDX_INCOME = 0;
const unsigned int PROCESS_IDX_OUTCOME = 1;
// 1 report at a time
const unsigned int SEND_DATA_COUNT = 1;

/**
 * Emulates outcome report.
 * @param i - accountant index
 * @return outcome reported by given accountant
 */
int getOutcome(const int i) {
    return (rand() % 1000) * (i+1);
}

/**
 * Emulates income report.
 * @param i - accountant index
 * @return income reported by given accountant
 */
int getIncome(const int i) {
    return (rand() % 1000) * (i+1);
}

int main(int argc, char* argv[]) {
    MPI_Status status;
    int processCount, accountantIdx;

    MPI_Init(&argc, &argv); // инициализация MPI библиотеки
    // threads amount within communication channe;
    MPI_Comm_rank(MPI_COMM_WORLD, &accountantIdx);
    // rank determination
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    int income, outcome, total = 0;

    const bool isRegularAccountant = (accountantIdx >= 0) && (accountantIdx < ACCOUNTANT_NUM);
    const bool isMainAccountant = (accountantIdx == ACCOUNTANT_NUM);

    // NOTE: Regular accountants reports statistics to the main one. The ...
    // ... main one fills the balance based on that data.
    if (isMainAccountant) {
        // all of the accountants excluding the main one
        for (unsigned  int i = 0; i < ACCOUNTANT_NUM; i++) {
            MPI_Recv(&income, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&outcome, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Fill balance based on gathered data
            total += income - outcome;
        }
        printf("Total: %d\n", total);
    } else if (isRegularAccountant) {
        income = getIncome(accountantIdx);
        outcome = getOutcome(accountantIdx);
        // Quick reference: signature MPI_Send(buf, count, datatype, dist, int tag, MPI_Comm comm)
        // * buf - initial position (address) of sending data;
        // * count - count of transferring data;
        // * datatype - type of transferring data;
        // * dest - ID of received within the group;
        // * tag - message ID;
        // * comm - communicator instance (MPI_COMM_WORLD => whole application)

        // -- send data to the main accountant
        MPI_Send(&income, SEND_DATA_COUNT, MPI_INT, ACCOUNTANT_NUM, PROCESS_IDX_INCOME, MPI_COMM_WORLD);
        MPI_Send(&outcome, SEND_DATA_COUNT, MPI_INT, ACCOUNTANT_NUM, PROCESS_IDX_OUTCOME, MPI_COMM_WORLD);
        printf("[Acc. %d/ proc. %d] Reported data: income = %d ; outcome = %d \n",
                accountantIdx,
                processCount - 1,
                income,
                outcome);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

