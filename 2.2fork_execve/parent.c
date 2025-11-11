#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            
}

int main() {
    int n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    bubbleSort(arr, n); // sort before sending

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("\n[CHILD] Created (PID = %d)\n", getpid());

        // Build argument list
        char *args[n + 3];
        args[0] = "./child"; // program to execute

        for (int i = 0; i < n; i++) {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }

        char *keyStr = malloc(10);
        sprintf(keyStr, "%d", key);
        args[n + 1] = keyStr;
        args[n + 2] = NULL; // end of args

        execv(args[0], args);
        perror("execv failed");
        exit(1);
    } 
    else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("\n[PARENT] Child finished execution.\n");
    } 
    else {
        perror("fork failed");
    }

    return 0;
}
