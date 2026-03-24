#include <stdio.h>
#define MAX 100

struct process {
    int pid;
    int type;   // 0 = System, 1 = User
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int rt;     // Remaining time (for preemptive if needed)
};

void sortByArrival(struct process p[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

// FCFS for a queue, starting at given time
void fcfs(struct process p[], int n, int start_time) {
    int time = start_time;
    for(int i=0; i<n; i++) {
        if(time < p[i].at)
            time = p[i].at;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        time = p[i].ct;
    }
}

void printProcesses(struct process p[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("ID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               (p[i].type == 0) ? "System" : "User",
               p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void ganttChart(struct process sys[], int sc, struct process user[], int uc) {
    printf("\nGantt Chart:\n|");
    for(int i=0; i<sc; i++) {
        printf(" P%d |", sys[i].pid);
    }
    for(int i=0; i<uc; i++) {
        printf(" P%d |", user[i].pid);
    }
    printf("\n0 ");
    for(int i=0; i<sc; i++) {
        printf("%d ", sys[i].ct);
    }
    for(int i=0; i<uc; i++) {
        printf("%d ", user[i].ct);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process sys[MAX], user[MAX];
    int sc = 0, uc = 0;

    for(int i=0; i<n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        int at; scanf("%d", &at);
        printf("Enter burst time: ");
        int bt; scanf("%d", &bt);
        printf("Enter type (0 = System, 1 = User): ");
        int type; scanf("%d", &type);

        struct process p = {i, type, at, bt, 0, 0, 0, bt};

        if(type == 0) sys[sc++] = p;
        else user[uc++] = p;
    }

    // Sort each queue by arrival time
    sortByArrival(sys, sc);
    sortByArrival(user, uc);

    // Run FCFS for system queue first (higher priority)
    fcfs(sys, sc, 0);
    int last_ct = (sc > 0) ? sys[sc - 1].ct : 0;

    // Run FCFS for user queue after system queue completes
    fcfs(user, uc, last_ct);

    // Print all processes together sorted by pid (optional)
    // For output exactly like sample, print system then user
    printProcesses(sys, sc);
    printProcesses(user, uc);

    ganttChart(sys, sc, user, uc);

    return 0;
}
