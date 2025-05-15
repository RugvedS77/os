// filename: bankers_simple.c
#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0}, safeSeq[10];

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canRun = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }

    if (count == n) {
        printf("System is in a safe state.\nSafe Sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    // Request algorithm
    char ch;
    printf("\nDo you want to make a request? (y/n): ");
    scanf(" %c", &ch);

    if (ch == 'y') {
        int req[10], p;
        printf("Enter process number: ");
        scanf("%d", &p);
        printf("Enter request for resources:\n");
        for (i = 0; i < m; i++)
            scanf("%d", &req[i]);

        int canGrant = 1;
        for (i = 0; i < m; i++) {
            if (req[i] > need[p][i] || req[i] > avail[i]) {
                canGrant = 0;
                break;
            }
        }

        if (canGrant) {
            for (i = 0; i < m; i++) {
                avail[i] -= req[i];
                alloc[p][i] += req[i];
                need[p][i] -= req[i];
            }
            printf("Request can be granted safely.\n");
        } else {
            printf("Request cannot be granted.\n");
        }
    }

    return 0;
}
