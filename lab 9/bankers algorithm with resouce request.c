#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX];
    int finish[MAX] = {0};
    int safeSeq[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Demand Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // 🔹 Resource Request Part
    int process;
    int request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    printf("Enter request for each resource:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    // Check Request <= Need
    for(int i = 0; i < m; i++) {
        if(request[i] > need[process][i]) {
            printf("Error: Request exceeds need.\n");
            return 0;
        }
    }

    // Check Request <= Available
    for(int i = 0; i < m; i++) {
        if(request[i] > avail[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend allocation
    for(int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // 🔹 Safety Algorithm
    int count = 0;

    // Reset finish array
    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is not in a safe state. Request denied.\n");
            return 0;
        }
    }

    printf("\nRequest granted.\n");
    printf("System is in a safe state.\n");

    printf("Safe sequence is: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}
