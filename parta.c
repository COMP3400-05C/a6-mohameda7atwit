#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Initializes an array of PCBs from an array of CPU bursts.
 * Allocates memory for blen PCBs, sets each with a unique PID,
 * the corresponding burst_left, and wait time initialized to 0.
 */
struct pcb* init_procs(int* bursts, int blen) {
    struct pcb* procs = (struct pcb*)malloc(blen * sizeof(struct pcb));
    if (procs == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < blen; i++) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }
    
    return procs;
}

/**
 * Prints all PCBs with their current state (PID, burst_left, wait time).
 * Helper function for debugging.
 */
void printall(struct pcb* procs, int plen) {
    for (int i = 0; i < plen; i++) {
        printf("PID %d: burst_left=%d, wait=%d\n", procs[i].pid, procs[i].burst_left, procs[i].wait);
    }
}

/**
 * Runs the current process for the specified amount of time.
 * Decreases the current process's burst_left by amount,
 * and increases wait time for other processes that still have burst left.
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    procs[current].burst_left -= amount;
    
    for (int i = 0; i < plen; i++) {
        if (i != current && procs[i].burst_left > 0) {
            procs[i].wait += amount;
        }
    }
}

/**
 * Runs First-Come-First-Serve (FCFS) scheduling.
 * Starts from process 0 and runs each process to completion in order.
 * Returns the total elapsed time when all processes are complete.
 */
int fcfs_run(struct pcb* procs, int plen) {
    int current_time = 0;
    
    for (int i = 0; i < plen; i++) {
        int burst = procs[i].burst_left;
        run_proc(procs, plen, i, burst);
        current_time += burst;
    }
    
    return current_time;
}

/**
 * Returns the next process to run in round-robin scheduling.
 * Moves to the next process in circular order, skipping completed processes.
 * Returns -1 if all processes are complete.
 */
int rr_next(int current, struct pcb* procs, int plen) {
    int next = (current + 1) % plen;
    int start = next;
    
    /* Find the next process that hasn't completed */
    while (procs[next].burst_left == 0) {
        next = (next + 1) % plen;
        /* If we've made a full loop, all processes are done */
        if (next == start) {
            return -1;
        }
    }
    
    return next;
}

/**
 * Runs Round-Robin (RR) scheduling with the specified time quantum.
 * Each process runs for up to quantum time units, then moves to the back of the queue.
 * Returns the total elapsed time when all processes are complete.
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    int current_time = 0;
    int current = 0;
    
    while (1) {
        /* Check if current process still has burst left */
        if (procs[current].burst_left > 0) {
            /* Run for min(quantum, burst_left) */
            int amount = (procs[current].burst_left < quantum) ? procs[current].burst_left : quantum;
            run_proc(procs, plen, current, amount);
            current_time += amount;
        }
        
        /* Find next process */
        int next = rr_next(current, procs, plen);
        if (next == -1) {
            /* All processes are done */
            break;
        }
        current = next;
    }
    
    return current_time;
}
