 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <unistd.h>

// Bubble Sort function (for parent)
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort function (for child)
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to display array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // ---- Child Process ----
        printf("\n[CHILD] Child Process ID: %d\n", getpid());
        printf("[CHILD] Parent Process ID: %d\n", getppid());

        insertionSort(arr, n);
        printf("[CHILD] Sorted using Insertion Sort:\n");
        display(arr, n);

        // Demonstrate Orphan process
        printf("[CHILD] Sleeping for 5 seconds to demonstrate orphan...\n");
        sleep(5);
        printf("[CHILD] After parent exit, my new parent PID is: %d\n", getppid());

        printf("[CHILD] Child process completed.\n");
        exit(0);
    }
    else {
        // ---- Parent Process ----
        printf("\n[PARENT] Parent Process ID: %d\n", getpid());
        printf("[PARENT] Child Process ID: %d\n", pid);

        bubbleSort(arr, n);
        printf("[PARENT] Sorted using Bubble Sort:\n");
        display(arr, n);

        // Uncomment the below line to demonstrate ZOMBIE state
        // sleep(10); // Parent sleeps, child finishes => child becomes zombie

        // Parent waits for child to finish (removes zombie)
        wait(NULL);
        printf("[PARENT] Child finished. Parent resuming work.\n");
        printf("[PARENT] Parent process completed.\n");
    }

    return 0;
}
