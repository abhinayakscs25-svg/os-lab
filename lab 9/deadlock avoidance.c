#include <stdio.h>

int main() {
    int n = 5, m = 3; // processes and resources

    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    int need[5][3];
    int finish[5] = {0};
    int safeSeq[5];

    // Calculate NEED matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j])
                        break;
                }

                if (j == m) {
                    // process can execute
                    for (int k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("System is NOT in safe state\n");
            return 0;
        }
    }

    // Print safe sequence
    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    return 0;
}
