#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "MT25092_Part_B_Workers.h"

/*
 * Program B:
 * Creates N threads using pthread
 * Each thread executes the selected worker function
 * Main thread waits for all threads using pthread_join
 */

typedef struct {
    char worker_type[8];
    int loops;
} thread_arg_t;

void *thread_func(void *arg)
{
    thread_arg_t *t = (thread_arg_t *)arg;
    run_worker(t->worker_type, t->loops);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <cpu|mem|io> <num_threads>\n", argv[0]);
        return 1;
    }

    char *worker_type = argv[1];
    int num_threads = atoi(argv[2]);

    if (num_threads <= 0) {
        printf("Number of threads must be > 0\n");
        return 1;
    }

    /* Roll no MT25092 → last digit = 2 → loops = 2000 */
    int loops = 2 * 1000;

    printf("Program B (Threads)\n");
    printf("Worker: %s | Threads: %d | Loops: %d\n",
           worker_type, num_threads, loops);

    pthread_t threads[num_threads];
    thread_arg_t args[num_threads];

    for (int i = 0; i < num_threads; i++) {
        strcpy(args[i].worker_type, worker_type);
        args[i].loops = loops;

        if (pthread_create(&threads[i], NULL, thread_func, &args[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
