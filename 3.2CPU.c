#include <stdio.h>
#include <limits.h>

struct Process {
    int id;          // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int waiting;     // Waiting time
    int turnaround;  // Turnaround time
    int remaining;   // Remaining burst time (for preemption)
};

// ---------- FCFS Scheduling ----------
void fcfs(struct Process p[], int n) {
    int time = 0; // current CPU time
    float total_wait = 0, total_turn = 0;

    printf("\n--- FCFS Scheduling ---\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival; // wait until process arrives

        p[i].waiting = time - p[i].arrival; // waiting time
        time += p[i].burst;                 // CPU executes this process
        p[i].turnaround = time - p[i].arrival; // turnaround time

        total_wait += p[i].waiting;
        total_turn += p[i].turnaround;
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turn / n);
}

// ---------- SJF (Preemptive) Scheduling ----------
void sjf_preemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    float total_wait = 0, total_turn = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst; // initialize remaining burst times

    printf("\n--- SJF (Preemptive) Scheduling ---\n");

    while (completed < n) {
        int idx = -1, min_remaining = INT_MAX;

        // find process with smallest remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_remaining) {
                min_remaining = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) { // no process available yet
            time++;
            continue;
        }

        // run process for 1 unit of time
        p[idx].remaining--;
        time++;

        // if process completes
        if (p[idx].remaining == 0) {
            completed++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            total_wait += p[idx].waiting;
            total_turn += p[idx].turnaround;
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turn / n);
}

// ---------- Main Menu ----------
int main() {
    struct Process p[10];
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    do {
        printf("\n1. FCFS\n2. SJF (Preemptive)\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
    
        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf_preemptive(p, n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0; 
}
