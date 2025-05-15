// filename: sjf_preemptive.c
#include <stdio.h>

int main() {
    int n, i, smallest, time, remain, temp;
    int at[10], bt[10], rt[10], wt = 0, tat = 0;
    float avg_wt, avg_tat;

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    rt[9] = 9999;
    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (time = 0, smallest = 9; remain != 0; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)
                smallest = i;
        }

        rt[smallest]--;

        if (rt[smallest] == 0) {
            remain--;
            int endTime = time + 1;
            printf("P%d\t%d\t\t%d\n", smallest+1, endTime - at[smallest], endTime - at[smallest] - bt[smallest]);
            wt += endTime - at[smallest] - bt[smallest];
            tat += endTime - at[smallest];
        }
    }

    avg_wt = (float)wt / n;
    avg_tat = (float)tat / n;
    printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time: %.2f\n", avg_wt, avg_tat);
    return 0;
}
