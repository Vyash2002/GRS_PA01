### Graduate Systems (CSE638) – PA01: Processes and Threads

**Name:** Yash Verma  
**Roll Number:** MT25092  
**Course:** Graduate Systems (CSE638)  
**Assignment:** PA01 – Processes and Threads

This project compares the behavior of **processes vs threads** for different types
of workloads: CPU-intensive, Memory-intensive, and I/O-intensive.

All programs are written in C and measurement is automated using Bash scripts.

---

## 📁 Files in This Folder

### Part A – Processes
- `MT25092_Part_A_Program_A.c`  
  Creates N child processes using `fork()`.  
  Each child runs one worker function (`cpu`, `mem`, or `io`).

### Part B – Threads
- `MT25092_Part_A_Program_B.c`  
  Creates N threads using `pthread_create()`.  
  Each thread runs one worker function.

- `MT25092_Part_B_Workers.c`  
  Implements the three worker functions:
  - `cpu_worker()` – CPU intensive (heavy floating point computation)
  - `mem_worker()` – Memory intensive (large memory access)
  - `io_worker()` – I/O intensive (forced disk writes using fsync)

- `MT25092_Part_B_Workers.h`  
  Header file containing worker function declarations.

---

### Part C – Measurement Script
- `MT25092_Part_C_shell.sh`  
  Automates execution of:
  - A + cpu
  - A + mem
  - A + io
  - B + cpu
  - B + mem
  - B + io

  Uses:
  - `taskset` → CPU pinning
  - `top` → CPU utilization
  - `iostat` → disk statistics
  - `time` → execution time

- `MT25092_Part_C_CSV.csv`  
  Stores measured CPU %, Disk TPS, and execution time.

---

### Part D – Scaling Experiments
- `MT25092_Part_D_shell.sh`  
  Runs programs with varying number of processes and threads.

- `MT25092_Part_D_CSV.csv`  
  Raw data for different process/thread counts.

- `MT25092_Part_D_plot.py`  
  Generates plots using matplotlib.

- `plots/`  
  Contains generated PNG plots.

---

### Build System
- `Makefile`  
  Compiles both programs:
  - `programA` → process-based program
  - `programB` → thread-based program

---

### Report
- `MT25092_Report.pdf`  
  Contains:
  - Screenshots
  - Observations
  - Graphs
  - Analysis
  - AI usage declaration
  - GitHub repository link

---

## ⚙️ Compilation

To compile both programs:

```bash
make
