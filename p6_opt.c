#include <stdio.h>

int search(int key, int frame[], int f) {
    for (int i = 0; i < f; i++)
        if (frame[i] == key) return 1;
    return 0;
}

int predict(int pages[], int frame[], int n, int index, int f) {
    int res = -1, farthest = index;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pages[50], frame[10], n, f;
    int hit = 0, fault = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, f)) {
            hit++;
        } else {
            int j;
            for (j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    break;
                }
            }

            if (j == f) {
                int pos = predict(pages, frame, n, i + 1, f);
                frame[pos] = pages[i];
            }
            fault++;
        }

        printf("Frames: ");
        for (int j = 0; j < f; j++) printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", fault);
    printf("Total Page Hits = %d\n", hit);
    return 0;
}
