#pragma once

#include <stdbool.h>
#include <stddef.h>

/** This struct contains various information about each process */
struct pcb {
    int pid;        /** The process ID */
    int burst_left; /** The amount of burst left */
    int wait;       /** The amount of time this process was stuck waiting */
};


struct pcb* init_procs(int* bursts, int blen);

void printall(struct pcb* procs, int plen);
void run_proc(struct pcb* procs, int plen, int current, int amount);

int fcfs_run(struct pcb* procs, int plen);

int rr_next(int current, struct pcb* procs, int plen);
int rr_run(struct pcb* procs, int plen, int quantum);

