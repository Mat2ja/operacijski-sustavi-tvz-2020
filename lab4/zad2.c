#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int zbroj = 0;

void *childZbroj();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing arguments\n");
        return -1;
    }

    int procCount = atoi(argv[1]);

    pthread_t *thread = calloc(procCount, sizeof(*thread));
    int *status;
    for (int i = 0; i < procCount; i++) {
        pthread_create(&thread[i], NULL, childZbroj, NULL);
    }
    for (int i = 0; i < procCount; i++) {
        pthread_join(thread[i], (void *)&status);
    }

    printf("Zbroj: %d\n", zbroj);

    free(thread);
    return 0;
}

void *childZbroj() {
    zbroj++;
    return 0;
}