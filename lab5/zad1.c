#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int seats[SIZE] = {};
pthread_mutex_t mutex[SIZE];

void *login();
void fetch();
void checkIn();
void writeToAPI();
int pickSeat();
int confirmChoice();
void mutex_init();
void mutex_destroy();

int main(int argc, char const *argv[]) {
    mutex_init();
    srand(time(NULL));

    pthread_t thread[SIZE] = {};
    for (int i = 0; i < SIZE; i++) {
        pthread_create(&thread[i], NULL, login, NULL);
    }
    for (int i = 0; i < SIZE; i++) {
        pthread_join(thread[i], NULL);
    }

    mutex_destroy();

    int free = 0;
    int taken = 0;
    int numOfSeats = sizeof(seats) / sizeof(seats[0]);
    for (int i = 0; i < numOfSeats; i++) {
        if (seats[i] == 0) {
            free++;
        } else {
            taken++;
        }
    }

    printf("Broj zauzetih sjedala: %d\n", taken);
    printf("Broj slobodnih sjedala: %d\n", free);

    return 0;
}

void *login() {
    checkIn();
    fetch();

    int choice = 0;
    while (1) {
        choice = pickSeat();
        pthread_mutex_lock(&mutex[choice]);
        if (seats[choice] == 0) {
            if (confirmChoice()) {
                writeToAPI();
                seats[choice] = 1;
                printf("Izabrano sjedalo %d\n", choice);
                pthread_mutex_unlock(&mutex[choice]);
                break;
            }
        }
        pthread_mutex_unlock(&mutex[choice]);
    }

    return 0;
}

void checkIn() {
    sleep(rand() % 5 + 1);
}

void fetch() {
    sleep(rand() % 3 + 1);
}

void writeToAPI() {
    sleep(rand() % 2 + 1);
}

int pickSeat() {
    return rand() % SIZE;
}

int confirmChoice() {
    return rand() % 2;
}

void mutex_init() {
    for (int i = 0; i < SIZE; i++) {
        assert(pthread_mutex_init(&mutex[i], NULL) == 0);
    }
}

void mutex_destroy() {
    for (int i = 0; i < SIZE; i++) {
        assert(pthread_mutex_destroy(&mutex[i]) == 0);
    }
}