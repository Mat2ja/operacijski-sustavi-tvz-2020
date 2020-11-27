#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *tin();
void *davor();
void *ivica();
void *ivan();
void *kuharica();

typedef struct {
    int brojPojedenih;
    int brojOdbijenih;
    int brojPraznih;
} eatStatus;

eatStatus tinStatus = {};
eatStatus davorStatus = {};
eatStatus ivicaStatus = {};
eatStatus ivanStatus = {};

void programiranje();
void spavanje();
void autoServis();
void TV();
void tenis();
void klavir();
void autoServis();
void aktivnost();
int jede(char *ime);
void printStatus(char *ime, eatStatus status);

int jelo = 0;
int brojJela;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing arguments\n");
    }

    srand(time(NULL));
    pthread_t thread[5];

    brojJela = atoi(argv[1]);

    int num = 5;
    pthread_create(&thread[0], NULL, tin, NULL);
    pthread_create(&thread[1], NULL, davor, NULL);
    pthread_create(&thread[2], NULL, ivica, NULL);
    pthread_create(&thread[3], NULL, ivan, NULL);
    pthread_create(&thread[4], NULL, kuharica, NULL);

    for (int i = 0; i < num; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("\nSTATUSI:");
    printStatus("Tin", tinStatus);
    printStatus("Davor", davorStatus);
    printStatus("Ivica", ivicaStatus);
    printStatus("Ivan", ivanStatus);

    return EXIT_SUCCESS;
}

void *tin() {
    char *ime = "Tin";
    while (brojJela > 0) {
        spavanje(ime);
        programiranje(ime);
        int res = jede(ime);
        if (res == 1)
            tinStatus.brojPojedenih++;
        else if (res == 0)
            tinStatus.brojOdbijenih++;
        else
            tinStatus.brojPraznih++;
        autoServis(ime);
    }
}
void *davor() {
    char *ime = "Davor";
    while (brojJela > 0) {
        spavanje(ime);
        programiranje(ime);
        int res = jede(ime);
        if (res == 1)
            davorStatus.brojPojedenih++;
        else if (res == 0)
            davorStatus.brojOdbijenih++;
        else
            davorStatus.brojPraznih++;
        TV(ime);
    }
}

void *ivica() {
    char *ime = "Ivica";
    while (brojJela > 0) {
        spavanje(ime);
        tenis(ime);
        int res = jede(ime);
        if (res == 1)
            ivicaStatus.brojPojedenih++;
        else if (res == 0)
            ivicaStatus.brojOdbijenih++;
        else
            ivicaStatus.brojPraznih++;
        programiranje(ime);
    }
}

void *ivan() {
    char *ime = "Ivan";
    while (brojJela > 0) {
        spavanje(ime);
        klavir(ime);
        int res = jede(ime);
        if (res == 1)
            ivanStatus.brojPojedenih++;
        else if (res == 0)
            ivanStatus.brojOdbijenih++;
        else
            ivanStatus.brojPraznih++;
        programiranje(ime);
    }
}

void *kuharica() {
    while (brojJela > 0) {
        if (jelo == 0) {
            //kuha
            sleep(rand() % 2 + 1);
            pthread_mutex_lock(&mutex);
            jelo = rand() % 8 + 1;
            printf("Na prazan stol je stavljeno jelo %d\n", jelo);
            pthread_mutex_unlock(&mutex);
            // odmara
            sleep(rand() % 2 + 1);
        }
    }
}

void spavanje(char *ime) {
    printf("%s sada spava\n", ime);
    sleep(rand() % 5 + 5);
}

void programiranje(char *ime) {
    printf("%s sada programira\n", ime);
    int num = rand() % 10 + 1;
    int res = 1;
    for (int i = 1; i <= num; i++) {
        res *= i;
    }
}

void autoServis(char *ime) {
    printf("%s je sada na auto-servisu\n", ime);
    int sansa = rand() % 100;
    if (sansa < 25) {
        sleep(4);
    } else if (sansa < 45) {
        sleep(2);
    } else {
        aktivnost();
    }
}

void TV(char *ime) {
    printf("%s gleda TV\n", ime);
    aktivnost();
}

void tenis(char *ime) {
    printf("%s igra tenis\n", ime);
    aktivnost();
}

void klavir(char *ime) {
    printf("%s slusa sviranje klavira\n", ime);
    aktivnost();
}

void aktivnost() {
    sleep(rand() % 4);
}

int jede(char *ime) {
    pthread_mutex_lock(&mutex);
    printf("%s je za stolom\n", ime);
    int statusValue;

    if (jelo == 0) {
        statusValue = -1;
        printf("%s je za praznim stolom\n", ime);
    } else if (!strcmp(ime, "Tin")) {
        if (jelo != 2 && jelo != 3) {
            printf("%s sada jede %d\n", ime, jelo);
            brojJela--;
            jelo = 0;
            statusValue = 1;
        } else {
            printf("%s odbija jelo %d\n", ime, jelo);
            statusValue = 0;
        }
    } else if (!strcmp(ime, "Davor")) {
        if (jelo != 1 && jelo != 6) {
            printf("%s sada jede %d\n", ime, jelo);
            brojJela--;
            jelo = 0;
            statusValue = 1;
        } else {
            printf("%s odbija jelo %d\n", ime, jelo);
            statusValue = 0;
        }
    } else if (!strcmp(ime, "Ivica")) {
        if (jelo != 5 && jelo != 7) {
            printf("%s sada jede %d\n", ime, jelo);
            brojJela--;
            jelo = 0;
            statusValue = 1;
        } else {
            printf("%s odbija jelo %d\n", ime, jelo);
            statusValue = 0;
        }
    } else if (!strcmp(ime, "Ivan")) {
        if (!strcmp(ime, "Ivan")) {
            if (jelo != 4) {
                printf("%s sada jede %d\n", ime, jelo);
                brojJela--;
                jelo = 0;
                statusValue = 1;
            } else {
                printf("%s odbija jelo %d\n", ime, jelo);
                statusValue = 0;
            }
        }
    }

    pthread_mutex_unlock(&mutex);
    return statusValue;
}

void printStatus(char *ime, eatStatus status) {
    printf("\n%s je jeo %d puta\n", ime, status.brojPojedenih);
    printf("%s je jelo odbio %d puta\n", ime, status.brojOdbijenih);
    printf("%s je %d puta naisao na prazan stol\n\n", ime, status.brojPraznih);
}
