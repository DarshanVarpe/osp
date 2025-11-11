#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20   // number of page references
#define PAGES 10 // page numbers range from 0 to 9

// ---------------------- FIFO Algorithm ----------------------
int fifo(int pages[], int n, int frames) {
    int memory[frames];
    int front = 0, pageFaults = 0;

    // initialize memory slots as empty (-1)
    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    // go through all page requests
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // check if page already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // if page not found → page fault occurs
        if (!found) {
            memory[front] = page;          // replace oldest page
            front = (front + 1) % frames;  // move front pointer circularly
            pageFaults++;
        }
    }
    return pageFaults;
}

// ---------------------- LRU Algorithm ----------------------
int lru(int pages[], int n, int frames) {
    int memory[frames], recent[frames];
    int pageFaults = 0;

    // initialize
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = -1;
    }

    // go through page requests
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // check if page already present
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                recent[j] = i;  // update last used time
                break;
            }
        }

        // if page not found → replace least recently used
        if (!found) {
            int least = 0;

            // find least recently used page
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[least])
                    least = j;
            }

            memory[least] = page;
            recent[least] = i;
            pageFaults++;
        }
    }
    return pageFaults;
}

// ---------------------- Main Function ----------------------
int main() {
    int pages[MAX];
    srand(time(0)); // randomize every run

    printf("\n---- PAGE REPLACEMENT SIMULATION ----\n");

    // Generate random reference string
    printf("\nRandom Page Reference String:\n");
    for (int i = 0; i < MAX; i++) {
        pages[i] = rand() % PAGES; // random 0–9
        printf("%d ", pages[i]);
    }
    printf("\n");

    // Table header
    printf("\nFrames\tFIFO Faults\tLRU Faults\n");
    printf("-------------------------------------\n");

    // Check for 1 to 7 frames
    for (int f = 1; f <= 7; f++) {
        int fifoFaults = fifo(pages, MAX, f);
        int lruFaults = lru(pages, MAX, f);

        printf("%d\t%d\t\t%d\n", f, fifoFaults, lruFaults);
    }

    printf("-------------------------------------\n");
    printf("\nNote:\nFIFO = First In First Out (replace oldest)\nLRU = Least Recently Used (replace least used page)\n");

    return 0;
}
