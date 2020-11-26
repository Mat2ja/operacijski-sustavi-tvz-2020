#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int seat[100] = {};

void *login();
void fetch();
void checkIn();
void writeToAPI();
int pickSeat();
int confirmChoice();

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    pthread_t thread[100] = {};
    for (int i = 0; i < 100; i++) {
        pthread_create(&thread[i], NULL, login, NULL);
    }
    for (int i = 0; i < 100; i++) {
        pthread_join(thread[i], NULL);
    }

    int free = 0;
    int taken = 0;
    int numOfSeats = sizeof(seat) / sizeof(seat[0]);
    for (int i = 0; i < numOfSeats; i++) {
        if (seat[i] == 0) {
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
        if (seat[choice] == 0) {
            if (confirmChoice()) {
                writeToAPI();
                seat[choice] = 1;
                printf("Izabrano sjedalo %d\n", choice);
                break;
            }
        }
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
    return rand() % 100;
}

int confirmChoice() {
    return rand() % 2;
}