#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
pthread_mutex_t lock;
sem_t empty, full;

void *producer(void *arg)
{
    int id = *(int *)arg;
    int i, item;

    for (i = 0; i < 5; i++) {
        item = id * 100 + i;
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        buffer[in] = item;
        printf("Producer %d inserted %d\n", id, item);
        in = (in + 1) % SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    int i, item;

    for (i = 0; i < 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);
        item = buffer[out];
        printf("Consumer %d removed %d\n", id, item);
        out = (out + 1) % SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t prod[2], cons[2];
    int id[2] = {1, 2};
    int i;

    pthread_mutex_init(&lock, NULL);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    for (i = 0; i < 2; i++)
        pthread_create(&prod[i], NULL, producer, &id[i]);
    for (i = 0; i < 2; i++)
        pthread_create(&cons[i], NULL, consumer, &id[i]);

    for (i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("Done.\n");
    return 0;
}
