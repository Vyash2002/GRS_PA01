#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "MT25092_Part_B_Workers.h"

/*
 * Program A:
 * Creates N child processes using fork()
 * Each child executes the selected worker function
 * Parent waits for all children to finish
 */

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <cpu|mem|io> <num_processes>\n", argv[0]);
        return 1;
    }

    char *worker_type = argv[1];
    int num_processes = atoi(argv[2]);

    if (num_processes <= 0) {
        printf("Number of processes must be > 0\n");
        return 1;
    }

    /* Roll no MT25092 → last digit = 2 → loops = 2000 */
    int loops = 2 * 1000;

    printf("Program A (Processes)\n");
    printf("Worker: %s | Processes: %d | Loops: %d\n",
           worker_type, num_processes, loops);

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {   // Child process
            run_worker(worker_type, loops);
            exit(0);
        }
    }

    /* Parent waits for all child processes */
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}
