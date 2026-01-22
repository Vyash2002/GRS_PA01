#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#include "MT25092_Part_B_Workers.h"

/* Dispatcher */
void run_worker(const char *type, int loops)
{
    if (strcmp(type, "cpu") == 0)
        cpu_worker(loops);
    else if (strcmp(type, "mem") == 0)
        mem_worker(loops);
    else if (strcmp(type, "io") == 0)
        io_worker(loops);
    else
        printf("Unknown worker type: %s\n", type);
}

/* ---------------- CPU Intensive ---------------- */
void cpu_worker(int loops)
{
    volatile double x = 0.0;

    for (int i = 0; i < loops*10; i++) {
        for (int j = 1; j < 50000; j++) {
            x += sqrt(i * j);
        }
    }
}

/* ---------------- Memory Intensive ---------------- */
void mem_worker(int loops)
{
    const int SIZE = 50 * 1024 * 1024; // ~50 MB
    char *arr = (char *)malloc(SIZE);

    if (!arr) {
        perror("malloc failed");
        return;
    }

    for (int i = 0; i < loops; i++) {
        for (int j = 0; j < SIZE; j += 64) { // touch each cache line
            arr[j]++;
        }
    }

    free(arr);
}

/* ---------------- IO Intensive ---------------- */
void io_worker(int loops)
{
    int fd = open("io_test_file.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("file open failed");
        return;
    }

    const int BUF_SIZE = 4096;
    char buffer[BUF_SIZE];
    memset(buffer, 'A', BUF_SIZE);

    for (int i = 0; i < loops; i++) {
        write(fd, buffer, BUF_SIZE);
        fsync(fd);   // force disk write (important for IO load)
    }

    close(fd);
}
