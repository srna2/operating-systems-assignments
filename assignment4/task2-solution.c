#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "assignment4.txt"

void write_message(int id) {
    char message[100];
    sprintf(message, "Message from Child %d\n", id);

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", message);
    fclose(file);
    exit(EXIT_SUCCESS);
}

int main() {
    pid_t pid;
    int i;

    for (i = 1; i <= 4; i++) {
        pid = fork();
        if (pid == -1) {
            perror("Failed to fork");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Child process
            write_message(i);
        }
    }

    for (i = 0; i < 4; i++) {
        wait(NULL);
    }

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return EXIT_FAILURE;
    }

    printf("Content of %s:\n", FILENAME);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
