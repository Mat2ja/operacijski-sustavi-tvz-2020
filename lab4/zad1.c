#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int zbroj = 0;

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    if (argc < 2) {
        printf("Missing arguments\n");
        return -1;
    }
    int procCount = atoi(argv[1]);

    for (int i = 0; i < procCount; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            zbroj++;
            exit(0);
        } else {
            wait(NULL);
        }
    }

    printf("Zbroj: %d\n", zbroj);

    return 0;
}
