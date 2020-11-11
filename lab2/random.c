#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char polje[100000];

int main(void) {
    srand(time(0));

    for (int i = 0; i < sizeof(polje); i++) {
        int randomValue = rand() % 2;
        if (randomValue == 1) {
            polje[i] = 1;
        } else if (randomValue == 0) {
            polje[i] = -1;
        }
    }

    for (int i = 0; i < sizeof(polje); i++) {
        printf("%d\n", polje[i]);
    }

    sleep(10);

    return 0;
}