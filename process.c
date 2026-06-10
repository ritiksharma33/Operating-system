#include <sys/types.h> // Fixed: Changed .hh to .h
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) { /* child process */
        
        // Using the confirmed path for your system
        execlp("/sbin/ping", "ping", "-c", "3", "google.com", NULL);
        
        // This code ONLY runs if execlp fails for some reason!
        perror("execlp failed"); 
        return 1; // Exit the child process with an error
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;
}