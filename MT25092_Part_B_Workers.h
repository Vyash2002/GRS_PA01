#ifndef MT25092_PART_B_WORKERS_H
#define MT25092_PART_B_WORKERS_H

void run_worker(const char *type, int loops);

void cpu_worker(int loops);
void mem_worker(int loops);
void io_worker(int loops);

#endif
