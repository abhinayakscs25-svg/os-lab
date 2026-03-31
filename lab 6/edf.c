#include <stdio.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline: ");
        scanf("%d", &p[i].deadline);

        printf("Period: ");
        scanf("%d", &p[i].period);
    }

    // -------- SCHEDULABILITY CHECK --------
    float utilization = 0;
    for (int i = 0; i < n; i++) {
        utilization += (float)p[i].bt / p[i].period;
    }

    printf("\nCPU Utilization = %.2f\n", utilization);

    if (utilization <= 1.0)
        printf("Task set is SCHEDULABLE under EDF\n");
    else
        printf("Task set is NOT SCHEDULABLE under EDF\n");

    // -------- EDF Scheduling --------
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].deadline > p[j].deadline) {
                swap(&p[i], &p[j]);
            }
        }
    }

    int time = 0;

    // -------- Gantt Chart --------
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].id);
    }

    printf("\n0");
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        printf("   %d", time);
    }

    // -------- Calculations --------
    time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\n\n===== EDF Scheduling =====\n");
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }

    return 0;
}

