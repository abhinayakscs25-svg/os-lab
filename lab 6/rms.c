#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int bt;
    int period;
    int deadline;
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

        printf("Period: ");
        scanf("%d", &p[i].period);

        printf("Deadline: ");
        scanf("%d", &p[i].deadline);
    }

    // -------- Utilization --------
    float U = 0.0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].bt / p[i].period;
    }

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\nCPU Utilization = %.2f\n", U);
    printf("RMS Bound = %.2f\n", bound);

    if (U <= bound)
        printf("Task set is SCHEDULABLE under RMS\n");
    else
        printf("Task set may NOT be schedulable under RMS\n");

    // -------- Sort by Period --------
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].period > p[j].period) {
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

    // -------- Calculate Times --------
    time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // -------- Output Table --------
    printf("\n\n===== RMS Scheduling =====\n");
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }

    // -------- Deadline Check --------
    printf("\nDeadline Check:\n");
    for (int i = 0; i < n; i++) {
        if (p[i].ct > p[i].deadline)
            printf("Process %d MISSED deadline\n", p[i].id);
        else
            printf("Process %d met deadline\n", p[i].id);
    }

    return 0;
}
