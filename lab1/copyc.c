#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Missing arguments\n");
        return -1;
    }

    // Check if buffer is valid before reading anything
    int bufferSize = atoi(argv[3]);
    if (!bufferSize || bufferSize < 1) {
        printf("Invalid buffer size\n");
        return -1;
    }

    printf("*** Copying from '%s' to '%s' (Buffer size: %dB) ***\n",
           argv[1], argv[2], bufferSize);

    // READ SOURCE FILE
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Error opening source file\n");
        return -1;
    }

    // READ DESTINATION FILE
    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        printf("Error opening destination file\n");
        return -1;
    }

    int buffer[bufferSize];
    int bytes;
    do {
        bytes = fread(buffer, 1, bufferSize, inputFile);
        if (fwrite(buffer, 1, bytes, outputFile) != bytes) {
            printf("Error writing into destination file\n");
            return -1;
        }
    } while (bytes > 0);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
