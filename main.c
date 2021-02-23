/* Kernel Simulator - Assignment 1, Part II
 *
 * Carleton University
 * Department of System and Computer Engineering
 * SYSC 4001 - Operating Systems
 * 
 * @authors			Trong Nguyen, 100848232
 *				Evan Smedley, 101148695 			
 * @version			v1.00
 * @release			February 5, 2021
 *
 * This program generates an executable file that simulates a small
 * OS kernel, which can be used for performance analysis of various
 * scheduling algorithms.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


// Structure implementation

typedef struct pcb {	// Defines the process control block struct
    int pid;
    int arrival_time;
    int remaining_CPU_time;
    int CPU_arrival_time;
    int io_frequency;
    int io_duration;
    struct pcb *next;
} pcb_t;

typedef struct {      // Queue struct holds pointers to the PCB that it contains
    pcb_t *front;
    pcb_t *rear;
    int size;
} queue_t;



// Allocating and initializing functions for structs

queue_t *new_queue(void) {
    /*
     * Allocates a queue struct on the heap and returns a pointer
     * to it. Initializes the front and rear pointers to null and the
     * queue size to 0.
     */
    queue_t *queue = malloc(sizeof(queue_t));     // Allocate new queue_t struct on the heap
    assert(queue != NULL);

    queue->front = NULL;			// Initialize elements of queue (the queue_t struct)
    queue->rear = NULL; 
    queue->size = 0;

    return queue;
}

pcb_t *new_pcb(int pid, int arrival_time, int total_CPU_time, int io_freq, int io_dur) {
    /*
     * Takes all of the inputted information about a process and stores it in a pcb_t struct
     * on the heap.
     */
    pcb_t *pcb = malloc(sizeof(pcb_t));
    assert(pcb != NULL);

    pcb->pid = pid;
    pcb->arrival_time = arrival_time;
    pcb->remaining_CPU_time = total_CPU_time;
    pcb->io_frequency = io_freq;
    pcb->io_duration = io_dur;
    pcb->next = NULL;

    return pcb;
}


// Queue and linked list functions

void enqueue(queue_t *queue, pcb_t *pcb) {
    /* 
     * Adds a previously allocated node to the end of the queue pointed to by queue.
     */
    if (queue->front == NULL) {		// If the queue is empty, add node at the front
        queue->front = pcb;
    } else {
        queue->rear->next = pcb;	//If the queue has other elements, add node at the end
    }

    queue->rear = pcb;     			// Set the rear pointer to point to the new end of the queue
    queue->size += 1;				// Increase queue size
}

void dequeue(queue_t *queue, _Bool deallocate) {
    /*
     * If the queue pointed to by queue is empty, returns false.
     * If the queue has one or more nodes, removes the front node
     * and returns true. If the queue ends up with only one node, 
     * makes sure that the front and rear pointers in the queue 
     * struct both point to the one node in the list.
     */
    if (queue->size == 0) {    		// If the queue is empty, cannot dequeue
        printf("Queue is empty, cannot dequeue.");
        assert(false);
    }
     pcb_t *pcb_to_delete = queue->front;       // Creates a temporary pointer to the front node

    if (deallocate == true) { 		// Determines whether node is deallocated or removed from list
        queue->front = queue->front->next;		// Remove the node from the queue, set new front
        free(pcb_to_delete);          			// Free the front node
        pcb_to_delete = NULL;
    } else {
        queue->front = queue->front->next;
        pcb_to_delete->next = NULL;
        
    }

    if (queue->front == NULL){		// If list is now empty, set front and rear pointers
        queue->rear = NULL;
    }

    queue->size -= 1;     			// Decrease queue size
}

pcb_t *front(queue_t *queue) {
    /*
     * Return a pointer to the first PCB in the queue.
     */
    return queue->front;
}


// Functions for writing to an output file
void erase_write_file(char writeFile[]) {
    /*
     * Write the array of characters to_be_written to the file specified by WRITE_FILE_NAME.
     */
    FILE *f1 = fopen(writeFile, "w");
    if (f1 == NULL) {
        printf("File was not opened");
        assert(false);
    }
    fclose(f1);
    f1 = NULL;
}


void transition(int transition_identifier, queue_t *old_state, queue_t *new_state, int time, char writeFile[]) {
    /*
     * Perform a transition between the states provided in old_state and 
     * new_state. The transition type is determined by the int transition_type:
     * - 0 is new to ready (admitted)
     * - 1 is ready to running (scheduler dispatch)
     * - 2 is running to waiting (I/O or event wait)
     * - 3 is waiting to ready (I/O or event completion)
     * - 4 is running to ready (interrupt)
     * - 5 is running to terminated (exit)
     * Information about the state change is displayed in the terminal and written to transitions.txt. 
     * The process is moved from one queue to the next.
     */
    
    // Open file specified by the macro WRITE_FILE_NAME. Print out some transition information.
    FILE *f2 = fopen(writeFile, "a");
    if (f2 == NULL) {
        printf("File was not opened");
        assert(false);
    }
    fprintf(f2, "%-14d %-14d ", time, old_state->front->pid);
    //fprintf(f2, "%d %d ", time, old_state->front->pid);

    // These if and else statements determine which states are being transitioned between and write
    // the corresponding states to the file pointer to by f. The commented out fprintf statements
    // can be used instead if you want the output file to be less formatted.
    if ((transition_identifier > 5) || (transition_identifier < 0)) {
        printf("Incorrect transition identifier");
        assert(false);
    } else if (transition_identifier == 0) {
        fprintf(f2, "NEW           READY\n\n");  
        //fprintf(f2, "NEW READY\n");
    } else if (transition_identifier == 1) {
        fprintf(f2, "READY         RUNNING\n\n");
        //fprintf(f2, "READY RUNNING\n");
    } else if (transition_identifier == 2) {
        fprintf(f2, "RUNNING       WAITING\n\n");
        //fprintf(f2, "RUNNING WAITING\n");
    } else if (transition_identifier == 3) {
        fprintf(f2, "WAITING       READY\n\n");
        //fprintf(f2, "WAITING READY\n");
    } else if (transition_identifier == 4) {
        fprintf(f2, "RUNNING       READY\n\n");
        //fprintf(f2, "RUNNING READY\n");
    } else {
        fprintf(f2, "RUNNING       TERMINATED\n\n");
        //fprintf(f2, "RUNNING TERMINATED \n");
    }
    fclose(f2);    					// Close the file pointed to by f.
    f2 = NULL;

    // Display transition details in the terminal (for debugging)
    //printf("Transition Time: %d, ", (time));
    //printf("Pid: %d\n\n", (old_state->front->pid));

    // Move the process from the old state to the new state
    enqueue(new_state, front(old_state));
    dequeue(old_state, false);
}



// Main Script

int main(int argc, char *argv[])
{
    // Asserts the correct number of arguments is passed
    if ((argc < 3) || (argc > 3)) {
        printf("Incorrect number of arguments");
        assert(false);
    }

    // Allocate an empty queue on the heap for each state in the diagram
    queue_t *new = new_queue();
    queue_t *ready = new_queue();
    queue_t *running = new_queue();
    queue_t *waiting = new_queue();
    queue_t *terminated = new_queue();

    // Remove all previous writing in WRITE_FILE_NAME
    erase_write_file(argv[2]);

    // Import processes from READ_FILE_NAME and add to array inputted_processes
    int pid;
    int arrival_time;
    int total_CPU_time;
    int io_freq;
    int io_dur;
    int num_processes = 0;

    FILE *f3 = fopen(argv[1], "r");
    assert(f3 != NULL);
    while (!feof(f3)) {
        fscanf(f3, "%d %d %d %d %d\n", &pid, &arrival_time, &total_CPU_time, &io_freq, &io_dur);
        num_processes++;
    }

    printf("num processes: %d\n\n", num_processes);

    pcb_t *inputted_processes[num_processes];

    rewind(f3);

    for (int i = 0; i < num_processes; i++) {
        fscanf(f3, "%d %d %d %d %d\n", &pid, &arrival_time, &total_CPU_time, &io_freq, &io_dur);
        inputted_processes[i] = new_pcb(pid, arrival_time, total_CPU_time, io_freq, io_dur);
    }
    fclose(f3);

    // Variable initialization for processing
    int time_elapsed = 0;
    int num_terminated = 0;
    int watchdog_timer = 500;
    int wait_until;

    while (num_processes > num_terminated) {

        // Add processes to new at their arrival time
        for (int j = 0; j < num_processes; j++) {
            if ((inputted_processes[j])->arrival_time == time_elapsed) {
                enqueue(new, inputted_processes[j]);
            }
        }

        // Move processes from new to ready (admit processes)
        while (new->size != 0) {
            transition(0, new, ready, time_elapsed, argv[2]);
        }
                
        // If there is a process in ready and running is empty, transition
        if ((ready->size > 0) && (running->size == 0)) {
            transition(1, ready, running, time_elapsed, argv[2]);
            running->front->CPU_arrival_time = time_elapsed;
        }

        // If there is a process in running, check if it needs to transition and update its
        // remaining CPU time.
        if (running->size > 0) {
            // If the process in running is done executing, move it from running to terminated
            if (running->front->remaining_CPU_time == 0) {
                transition(5, running, terminated, time_elapsed, argv[2]);
                dequeue(terminated, true);
                num_terminated++;
            
            // If the process in running needs I/O, transition from running to waiting
            } else if ((time_elapsed - running->front->CPU_arrival_time) == running->front->io_frequency) {
                transition(2, running, waiting, time_elapsed, argv[2]);
                if (waiting->size == 1) {
                    wait_until = time_elapsed + waiting->front->io_duration;
                }
            
            // If an interrupt is triggered because a process has been in running for too long,
			// transition to ready.
            } else if ((time_elapsed - running->front->CPU_arrival_time) > watchdog_timer) {
                transition(4, running, ready, time_elapsed, argv[2]);
            } else {
                running->front->remaining_CPU_time -= 1;
            }
        }

        // If there is a process in waiting and it is done, transition to ready and 
		// set wait_until for the new process.
        if ((time_elapsed == wait_until) && (waiting->size > 0)) {
            transition(3, waiting, ready, time_elapsed, argv[2]);
            if (waiting->size > 0) {
                wait_until = time_elapsed + waiting->front->io_duration;
            }
        }
        
        time_elapsed++;
    }

    free(new);
    free(ready);
    free(running);
    free(waiting);
    free(terminated);

    return 0;
}
