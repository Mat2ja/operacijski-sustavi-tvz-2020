#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    if (argc < 2) {
        printf("Missing arguments\n");
        return -1;
    }

    int procCount = atoi(argv[1]);

    for (int i = 0; i < procCount; i++) {
        pid_t pid = fork();

        switch (pid) {
        case -1:
            printf("Unable to create child process\n");
            exit(EXIT_FAILURE);
        case 0:
            printf("Dijete #%d\n", i + 1);
            exit(0);
        default:
            printf("Roditelj #%d %d\n", i + 1, getppid());
            wait(NULL);
        }
    }

    return 0;
}
