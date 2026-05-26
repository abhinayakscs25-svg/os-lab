#include <stdio.h>

int main() {
    int pages[20], frames[10], n, f, i, j, k, faults;

    printf("Enter no. of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter no. of frames: ");
    scanf("%d", &f);

    // FIFO
    faults = 0;
    for(i = 0; i < f; i++) frames[i] = -1;

    int index = 0;
    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++)
            if(frames[j] == pages[i]) found = 1;

        if(!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }
    printf("\nFIFO Page Faults = %d", faults);

    // LRU
    int time[10], cnt = 0;
    faults = 0;

    for(i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                cnt++;
                time[j] = cnt;
                found = 1;
            }
        }

        if(!found) {
            int min = time[0], pos = 0;

            for(j = 1; j < f; j++) {
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            cnt++;
            time[pos] = cnt;
            faults++;
        }
    }
    printf("\nLRU Page Faults = %d", faults);

    // Optimal
    faults = 0;
    for(i = 0; i < f; i++) frames[i] = -1;

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++)
            if(frames[j] == pages[i]) found = 1;

        if(!found) {
            int pos = -1, farthest = i;

            for(j = 0; j < f; j++) {
                int next;
                for(next = i + 1; next < n; next++)
                    if(frames[j] == pages[next]) break;

                if(next > farthest) {
                    farthest = next;
                    pos = j;
                }
            }

            if(pos == -1) pos = 0;

            frames[pos] = pages[i];
            faults++;
        }
    }
    printf("\nOptimal Page Faults = %d", faults);

    return 0;
}
