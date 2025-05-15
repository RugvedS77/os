// filename: round_robin.c
#include <stdio.h>

int main() {
    int i, n, time, remain, temps, time_quantum;
    int wt = 0, tat = 0, bt[10], rt[10];

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (time = 0, i = 0; remain != 0;) {
        if (rt[i] > 0 && rt[i] <= time_quantum) {
            time += rt[i];
            rt[i] = 0;
            remain--;
            printf("P%d\t%d\t\t%d\n", i+1, time, time - bt[i]);
            wt += time - bt[i];
            tat += time;
        } else if (rt[i] > 0) {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        i = (i + 1) % n;
    }

    printf("\nAverage Waiting Time: %.2f", (float)wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)tat/n);
    return 0;
}
