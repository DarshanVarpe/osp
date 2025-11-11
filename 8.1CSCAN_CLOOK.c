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


void cscan(int requests[], int n, int head) {
    int total_movement = 0;
    int curr = head;
    int seq[n];
    int idx = 0;

    // sort requests
    sort_int(requests, n);

    // separate into right and left of head
    int right[n], left[n];
    int rn=0, ln=0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            right[rn] = requests[i];
            rn++;
        } else {
            left[ln] = requests[i];
            ln++;
        }
    }

    // Move towards end (499) first
    for (int i = 0; i < rn; i++) {
        seq[idx] = right[i];
        idx++;
        total_movement += abs(curr - right[i]);
        curr = right[i];
    }

    // Go to end of disk (DISK_SIZE-1) then jump to start (0)
    if (curr != DISK_SIZE-1) {
        total_movement += abs(curr - (DISK_SIZE-1));
        curr = DISK_SIZE-1;
    }
    // Jump to start — this jump still counts as movement for calculation
    total_movement += abs(curr - 0);
    curr = 0;

    // Then service the left side requests
    for (int i = 0; i < ln; i++) {
        seq[idx] = left[i];
        idx++;
        total_movement += abs(curr - left[i]);
        curr = left[i];
    }

    // Print results
    printf("C-SCAN sequence: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
    printf("C-SCAN total head movement = %d\n", total_movement);
    printf("C-SCAN average seek distance = %.2f\n\n", (float)total_movement / n);
}


void clook(int requests[], int n, int head) {
    int total_movement = 0;
    int curr = head;
    int seq[n];
    int idx = 0;

    // sort requests
    sort_int(requests, n);

    // separate into right and left of head
    int right[n], left[n];
    int rn=0, ln=0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            right[rn++] = requests[i];
        } else {
            left[ln++] = requests[i];
        }
    }

    // Move towards higher cylinders first
    for (int i = 0; i < rn; i++) {
        seq[idx++] = right[i];
        total_movement += abs(curr - right[i]);
        curr = right[i];
    }

    // Jump to the lowest request on left (if any)
    if (ln > 0) {
        total_movement += abs(curr - left[0]);
        curr = left[0];
        // Then serve left ones
        for (int i = 0; i < ln; i++) {
            seq[idx++] = left[i];
            total_movement += abs(curr - left[i]);
            curr = left[i];
        }
    }

    // Print results
    printf("C-LOOK sequence: ");
    for (int i = 0; i < idx; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
    printf("C-LOOK total head movement = %d\n", total_movement);
    printf("C-LOOK average seek distance = %.2f\n\n", (float)total_movement / n);
}

int main() {
    int requests1[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n1 = sizeof(requests1)/sizeof(requests1[0]);
    int head1 = 85;

    printf("=== Part 8.1 (C-SCAN & C-LOOK) ===\n");
    cscan(requests1, n1, head1);
    clook(requests1, n1, head1);

    return 0;
}


