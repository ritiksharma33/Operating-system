// Save this file as parallel_dynamic.c

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h> // Needed for exit()

int main(int argc, char *argv[])
{
    int i;
    pid_t pid;

    // Check if the user provided at least one filename.
    // We check for less than 2 because argv[0] is the program name.
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    printf("Parent starting...\n");

    // Loop from 1 to argc-1 to process each filename provided.
    for (i = 1; i < argc; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }
        else if (pid == 0) {
            // This is the child's code.
            printf("--> Child (PID: %d) processing %s\n", getpid(), argv[i]);
            
            execlp("/usr/bin/wc", "wc", argv[i], NULL);
            
            // This code only runs if execlp fails
            perror("execlp failed");
            exit(1); // Use exit() in child to avoid issues
        }
    }

    // Parent waits for all children to finish.
    // The number of children is argc - 1.
    printf("Parent waiting for %d children...\n", argc - 1);
    for (i = 1; i < argc; i++) {
        wait(NULL);
    }

    printf("All children have finished. Parent is done.\n");

    return 0;
}