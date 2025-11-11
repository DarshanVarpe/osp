#include <stdio.h>

#define MAX 10 // maximum number of processes and resources

int n, m; // n = number of processes, m = number of resources
int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
int finish[MAX], safeSeq[MAX];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
}

int isSafe() {
    int work[MAX];
    for (int i = 0; i < m; i++)
        work[i] = avail[i]; // copy available resources

    for (int i = 0; i < n; i++)
        finish[i] = 0; // initially, no process is finished

    int count = 0;

    while (count < n) {
        int found = 0; // to check if at least one process can run

        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) { // process not finished yet
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break; // this process cannot run now

                if (j == m) { // all needs <= available
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k]; // release resources
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (!found) // if no process can run, system is unsafe
            return 0;
    }

    printf("\nSystem is in SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources: ");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    calculateNeed();

    if (!isSafe()) {
        printf("\nSystem is in UNSAFE state.\n");
        return 0;
    }

    // Resource request part
    int reqProcess, request[MAX];
    printf("\nEnter process number making request (0 - %d): ", n - 1);
    scanf("%d", &reqProcess);

    printf("Enter request for %d resources: ", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Step 1: Request <= Need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[reqProcess][i]) {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    // Step 2: Request <= Available
    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // Step 3: Pretend to allocate
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[reqProcess][i] += request[i];
        need[reqProcess][i] -= request[i];
    }

    // Step 4: Check if still safe
    if (isSafe())
        printf("\nRequest can be GRANTED safely.\n");
    else {
        printf("\nRequest CANNOT be granted (unsafe state).\n");
        // Rollback (undo changes)
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[reqProcess][i] -= request[i];
            need[reqProcess][i] += request[i];
        }
    }

    return 0;
}
