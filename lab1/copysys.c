#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        write(2, "Missing arguments\n", 19);
        exit(EXIT_FAILURE);
    }

    // Check if buffer is valid before reading/creating anything
    int bufferSize = atoi(argv[3]);
    if (!bufferSize || bufferSize < 1) {
        write(2, "Invalid buffer size\n", 21);
        exit(EXIT_FAILURE);
    }

    printf("*** Copying from '%s' to '%s' (Buffer size: %dB) ***\n",
           argv[1], argv[2], bufferSize);

    // READ SOURCE FILE
    int inputFile = open(argv[1], O_RDONLY);
    if (inputFile < 0) {
        write(2, "Error opening source file\n", 27);
        exit(EXIT_FAILURE);
    }

    // READ DESTINATION FILE
    int outputFile = open(argv[2],
                          O_CREAT | O_WRONLY | O_TRUNC,
                          00400 | 00200 | 00040 | 00004);
    if (outputFile < 0) {
        write(2, "Error opening destination file\n", 32);
        exit(EXIT_FAILURE);
    }

    int buffer[bufferSize];
    int bytes;
    do {
        bytes = read(inputFile, buffer, bufferSize);
        if (write(outputFile, buffer, bytes) != bytes) {
            write(2, "Error writing into destination file\n", 37);
            exit(EXIT_FAILURE);
        }

    } while (bytes > 0);

    close(inputFile);
    close(outputFile);

    return 0;
}