// readers_writers.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t db;               // Controls access to the shared database
pthread_mutex_t mutex;  // Protects readerCount variable

int readerCount = 0;    // Number of readers currently reading

void* reader(void* id) {
    int readerID = *(int*)id;

    while (1) {
        // Reader wants to read
        pthread_mutex_lock(&mutex);
        readerCount++;
        if (readerCount == 1)
            sem_wait(&db);  // first reader locks the database for writers

        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader %d is reading flight data.\n", readerID);
        sleep(1); // simulate reading time
        printf("Reader %d finished reading.\n", readerID);

        // Reader finished
        pthread_mutex_lock(&mutex);
        readerCount--;
        if (readerCount == 0)
            sem_post(&db);  // last reader unlocks database for writers
            
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3 + 1); // random delay before reading again
    }
    return NULL;
}

void* writer(void* id) {
    int writerID = *(int*)id;

    while (1) {
        // Writer wants to write (book a flight)
        sem_wait(&db);  // wait for exclusive access
        printf("Writer %d is updating flight reservations.\n", writerID);
        sleep(2); // simulate writing time
        printf("Writer %d finished updating.\n", writerID);
        sem_post(&db);  // release access

        sleep(rand() % 4 + 1); // random delay before writing again
    }
    return NULL;
}

int main() {
    pthread_t rtid[5], wtid[2];
    int rID[5], wID[2];

    sem_init(&db, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; i++) {
        rID[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &rID[i]);
    }

    for (int i = 0; i < 2; i++) {
        wID[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &wID[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    sem_destroy(&db);
    pthread_mutex_destroy(&mutex);

    return 0;
}
