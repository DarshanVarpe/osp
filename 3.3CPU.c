#include <stdio.h>

struct Process {
    int id;          // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int remaining;   // Remaining burst time
    int waiting;     // Waiting time
    int turnaround;  // Turnaround time
};

void roundRobin(struct Process p[], int n, int quantum) {
    int time = 0; // current time
    int completed = 0; // number of finished processes
    float total_wait = 0, total_turn = 0;

    // Make a copy of burst time
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    printf("\n--- Round Robin Scheduling (Time Quantum = %d) ---\n", quantum);
    printf("\nGANTT CHART:\n|");

    while (completed < n) {
        int done = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                done = 1;

                // Print process execution in Gantt chart
                printf(" P%d |", p[i].id);

                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].waiting = time - p[i].arrival - p[i].burst;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].remaining = 0;
                    completed++;
                    total_wait += p[i].waiting;
                    total_turn += p[i].turnaround;
                }
            }
        }
        if (!done)
            time++; // no process has arrived yet
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f", total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turn / n);
}

void fcfs(struct Process p[], int n) {
    int time = 0;
    float total_wait = 0, total_turn = 0;

    printf("\n--- FCFS Scheduling ---\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = time - p[i].arrival;

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
        printf("\n1. FCFS\n2. Round Robin (Preemptive)\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                roundRobin(p, n, 2); // time quantum = 2
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
