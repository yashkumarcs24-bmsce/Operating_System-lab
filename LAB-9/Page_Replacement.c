#include <stdio.h>
void FIFO(int pages[], int n, int frames) {
    int frame[frames];
    int i, j, k = 0, pageFaults = 0, found;
    for (i = 0; i < frames; i++)
        frame[i] = -1;
    printf("\nFIFO Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[k] = pages[i];
            k = (k + 1) % frames;
            pageFaults++;
        }
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
void LRU(int pages[], int n, int frames) {
    int frame[frames], recent[frames];
    int i, j, pos, found, pageFaults = 0;
    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }
    printf("\nLRU Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                recent[j] = i;
                break;
            }
        }
        if (!found) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (recent[j] < recent[pos])
                    pos = j;
            }
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            frame[pos] = pages[i];
            recent[pos] = i;
            pageFaults++;
        }
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
void Optimal(int pages[], int n, int frames) {
    int frame[frames];
    int i, j, k, found, pageFaults = 0;
    int pos, farthest;
    for (i = 0; i < frames; i++)
        frame[i] = -1;
    printf("\nOptimal Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            pageFaults++;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                farthest = -1;
                pos = -1;
                for (j = 0; j < frames; j++) {
                    int nextUse = n;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }
                frame[pos] = pages[i];
            }
        }
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
int main() {
    int n, frames, i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    Optimal(pages, n, frames);
    return 0;
}