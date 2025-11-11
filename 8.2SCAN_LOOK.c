#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 500

void sort_int(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void scan_algo(int requests[], int n, int head) {
    int total_movement = 0;
    int curr = head;
    int seq[n];
    int idx = 0;

    sort_int(requests, n);

    int right[n], left[n];
    int rn=0, ln=0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            right[rn++] = requests[i];
        } else {
            left[ln++] = requests[i];
        }
    }

    // Move right first (towards 499)
    for (int i = 0; i < rn; i++) {
        seq[idx++] = right[i];
        total_movement += abs(curr - right[i]);
        curr = right[i];
    }

    // Go to end (499)
    if (curr != DISK_SIZE-1) {
        total_movement += abs(curr - (DISK_SIZE-1));
        curr = DISK_SIZE-1;
    }

    // Then reverse direction and serve left side in descending order
    for (int i = ln-1; i >= 0; i--) {
        seq[idx++] = left[i];
        total_movement += abs(curr - left[i]);
        curr = left[i];
    }

    printf("SCAN sequence: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
    printf("SCAN total head movement = %d\n", total_movement);
    printf("SCAN average seek distance = %.2f\n\n", (float)total_movement / n);
}

void look_algo(int requests[], int n, int head) {
    int total_movement = 0;
    int curr = head;
    int seq[n];
    int idx = 0;

    sort_int(requests, n);

    int right[n], left[n];
    int rn=0, ln=0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            right[rn++] = requests[i];
        } else {
            left[ln++] = requests[i];
        }
    }

    // Move right only to last request
    for (int i = 0; i < rn; i++) {
        seq[idx++] = right[i];
        total_movement += abs(curr - right[i]);
        curr = right[i];
    }

    // Then reverse direction and serve left side in descending order
    for (int i = ln-1; i >= 0; i--) {
        seq[idx++] = left[i];
        total_movement += abs(curr - left[i]);
        curr = left[i];
    }

    printf("LOOK sequence: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
    printf("LOOK total head movement = %d\n", total_movement);
    printf("LOOK average seek distance = %.2f\n\n", (float)total_movement / n);
}

int main() {
    int requests2[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n2 = sizeof(requests2)/sizeof(requests2[0]);
    int head2 = 185;

    printf("=== Part 8.2 (SCAN & LOOK) ===\n");
    scan_algo(requests2, n2, head2);
    look_algo(requests2, n2, head2);

    return 0;
}
