#include <stdio.h>

int main() {
    int n, i, qn;

    // Input: number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n];

    // Input: burst times
    for(i = 0; i < n; i++) {
        printf("Enter BT of P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Input: number of quantum values
    printf("Enter number of quantum values: ");
    scanf("%d", &qn);

    // Loop for different quantum values
    while(qn--) {
        int q;
        printf("\nEnter Time Quantum: ");
        scanf("%d", &q);

        int rt[n], wt[n], tat[n];
        int time = 0, done;

        // Initialize remaining time
        for(i = 0; i < n; i++)
            rt[i] = bt[i];

        // -------- GANTT CHART --------
        printf("\nGantt Chart:\n| ");

        do {
            done = 1;

            for(i = 0; i < n; i++) {
                if(rt[i] > 0) {
                    done = 0;

                    if(rt[i] <= q) {
                        time += rt[i];
                        rt[i] = 0;

                        tat[i] = time;            // Completion Time
                        wt[i] = tat[i] - bt[i];  // Waiting Time
                    } else {
                        time += q;
                        rt[i] -= q;
                    }

                    printf("P%d | ", i + 1);
                }
            }

        } while(!done);

        // -------- TIME LINE --------
        printf("\n0 ");
        int t = 0;

        for(i = 0; i < n; i++)
            rt[i] = bt[i];

        do {
            done = 1;

            for(i = 0; i < n; i++) {
                if(rt[i] > 0) {
                    done = 0;

                    if(rt[i] <= q) {
                        t += rt[i];
                        rt[i] = 0;
                    } else {
                        t += q;
                        rt[i] -= q;
                    }

                    printf("%d ", t);
                }
            }

        } while(!done);

        // -------- TABLE --------
        float total_wt = 0, total_tat = 0;

        printf("\n\nProcess\tBT\tCT\tWT\tTAT\tRT\n");

        for(i = 0; i < n; i++) {
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                   i + 1,
                   bt[i],
                   tat[i],      // CT
                   wt[i],
                   tat[i],      // TAT
                   0);          // RT (final)

            total_wt += wt[i];
            total_tat += tat[i];
        }

        printf("\nAverage WT  = %.2f", total_wt / n);
        printf("\nAverage TAT = %.2f\n", total_tat / n);
    }

    return 0;
}
