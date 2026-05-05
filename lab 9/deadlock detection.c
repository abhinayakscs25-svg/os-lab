#include <stdio.h>

int main() {
    int n = 3, m = 2; // Processes and Resources

    int allocation[3][2] = {
        {1, 0},
        {0, 1},
        {1, 1}
    };

    int request[3][2] = {
        {1, 1},
        {1, 0},
        {0, 1}
    };

    int available[2] = {0, 0};

    int finish[3] = {0}; // Initially all processes are unfinished

    int work[2];
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int found;

    do {
        found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    // Process can finish
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while (found);

    // Check deadlock
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0)
            printf("Deadlock: P%d\n", i);
    }

    return 0;
}
