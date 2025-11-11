#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Function to print first n prime numbers
void printPrimes(int n) {
    int count = 0, num = 2;
    while (count < n) {
        if (isPrime(num)) {
            printf("%d ", num);
            count++;
        }
        num++;
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter how many prime numbers you want: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 0;
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("\n[CHILD] PID = %d\n", getpid());
        printf("[CHILD] Generating first %d prime numbers:\n", n);
        printPrimes(n);
        printf("[CHILD] Done printing primes.\n");
    }
    else {
        // Parent process
        printf("\n[PARENT] PID = %d waiting for child...\n", getpid());
        wait(NULL); // Wait until child completes
        printf("[PARENT] Child finished. Parent exiting.\n");
    }

    return 0;
}
