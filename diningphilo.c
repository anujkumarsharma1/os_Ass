#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chopstick[5];

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % 5;

    printf("Philosopher %d is hungry\n", id);

    if (id == 4) {
        sem_wait(&chopstick[right]);
        sem_wait(&chopstick[left]);
    } else {
        sem_wait(&chopstick[left]);
        sem_wait(&chopstick[right]);
    }

    printf("Philosopher %d is eating\n", id);
    sleep(1);
    printf("Philosopher %d finished eating\n", id);

    sem_post(&chopstick[left]);
    sem_post(&chopstick[right]);
    return NULL;
}

int main()
{
    pthread_t tid[5];
    int id[5];
    int i;

    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for (i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &id[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);

    for (i = 0; i < 5; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}
