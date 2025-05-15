#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2], pipe2[2];
    char msg1[] = "Hi from parent!";
    char msg2[] = "Hello from child!";
    char buffer[100];

    pipe(pipe1); // Parent to child
    pipe(pipe2); // Child to parent

    if (fork() == 0) {
        // Child process
        close(pipe1[1]); // Close write end of pipe1
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(pipe2[0]); // Close read end of pipe2
        write(pipe2[1], msg2, strlen(msg2) + 1);
    } else {
        // Parent process
        close(pipe1[0]); // Close read end of pipe1
        write(pipe1[1], msg1, strlen(msg1) + 1);

        close(pipe2[1]); // Close write end of pipe2
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
    }

    return 0;
}
