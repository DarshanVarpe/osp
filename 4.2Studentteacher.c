// sleeping_ta.c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h> 

#define NUM_STUDENTS 5
#define NUM_CHAIRS 3

sem_t students;
sem_t ta;
pthread_mutex_t mutex;

int waitingStudents = 0;

void* student(void* id) {
    int studentID = *(int*)id;
    while (1) {
        sleep(rand() % 5 + 1);  // student arrives randomly

        pthread_mutex_lock(&mutex);
        if (waitingStudents < NUM_CHAIRS) {
            waitingStudents++;
            printf("Student %d waiting. Waiting students: %d\n", studentID, waitingStudents);
            sem_post(&students);
            pthread_mutex_unlock(&mutex);
            sem_wait(&ta); // Wait for TA help
            printf("Student %d getting help from TA.\n", studentID);
        } else {
            pthread_mutex_unlock(&mutex);
            printf("No chair available. Student %d will come later.\n", studentID);
        }
    }
}

void* teachingAssistant(void* arg) {
    while (1) {
        sem_wait(&students);  // Wait for student
        pthread_mutex_lock(&mutex);
        waitingStudents--;
        printf("TA is helping a student. Students waiting: %d\n", waitingStudents);
        pthread_mutex_unlock(&mutex);
        sem_post(&ta);  // Signal student
        sleep(2);  // time to help student
        printf("TA finished helping a student.\n");
    }
}

int main() {
    pthread_t taThread, studentThreads[NUM_STUDENTS];
    int ids[NUM_STUDENTS];

    sem_init(&students, 0, 0);
    sem_init(&ta, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&taThread, NULL, teachingAssistant, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&studentThreads[i], NULL, student, &ids[i]);
    }

    pthread_join(taThread, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(studentThreads[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&students);
    sem_destroy(&ta);

    return 0;
}
