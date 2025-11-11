// producer_consumer_file.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>   // for sleep and usleep

pthread_mutex_t mutex;
sem_t dataReady;   // signaled when producer writes data
sem_t dataConsumed; // signaled when consumer reads data

void* producer(void* arg) {
    FILE* file;
    int value;

    while (1) {
        value = rand() % 10; // generate number between 0–9
        usleep((rand() % 101) * 1000); // random 0–100ms delay

        // Wait until consumer has read previous data
        sem_wait(&dataConsumed);

        pthread_mutex_lock(&mutex);
        file = fopen("shared_data.txt", "w");
        if (file == NULL) {
            perror("Error opening file");
            pthread_mutex_unlock(&mutex);
            continue;
        }

        fprintf(file, "%d\n", value);
        fclose(file);
        printf("Producer: wrote %d to file\n", value);
        pthread_mutex_unlock(&mutex);

        // Signal to consumer that new data is ready
        sem_post(&dataReady);
    }
    return NULL;
}

void* consumer(void* arg) {
    FILE* file;
    int value;

    while (1) {
        // Wait for producer to signal data ready
        sem_wait(&dataReady);

        pthread_mutex_lock(&mutex);
        file = fopen("shared_data.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            pthread_mutex_unlock(&mutex);
            continue;
        }

        fscanf(file, "%d", &value);
        fclose(file);
        printf("Consumer: read %d from file\n", value);
        pthread_mutex_unlock(&mutex);

        // Tell producer that consumer is done
        sem_post(&dataConsumed);
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    sem_init(&dataReady, 0, 0);
    sem_init(&dataConsumed, 0, 1); // start with “data consumed”

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&dataReady);
    sem_destroy(&dataConsumed);

    return 0;
}
