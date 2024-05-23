#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MAX_QUEUE_SIZE 50
#define RAM_SIZE 2048
#define HIGH_PRIORITY_QUEUE 1
#define MEDIUM_PRIORITY_QUEUE 2
#define LOW_PRIORITY_QUEUE 3

// Process structure
typedef struct {
    char name[5];
    int arrival_time;
    int priority;
    int burst_time;
    int ram_required;
    int cpu_rate;
} Process;

// Queue structure
typedef struct {
    Process* arr[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Function prototypes
void fcfs_scheduler(Process* processes, int num_processes, FILE* output_file);
void add_process_to_queue(Process* process, Queue* queue);
Process* remove_process_from_queue(Queue* queue);
int is_queue_empty(Queue* queue);

int main() {
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files!\n");
        return 1;
    }

    Process processes[MAX_PROCESSES];
    int num_processes = 0;

    // Read processes from input file
    while (fscanf(input_file, "%[^,],%d,%d,%d,%d,%d\n", processes[num_processes].name,
        &processes[num_processes].arrival_time, &processes[num_processes].priority,
        &processes[num_processes].burst_time, &processes[num_processes].ram_required,
        &processes[num_processes].cpu_rate) == 6) {
        num_processes++;
    }

    fclose(input_file);

    // Perform scheduling
    fcfs_scheduler(processes, num_processes, output_file);

    fclose(output_file);

    // Print the queues for demonstration purposes
    printf("CPU-1 que1(priority-0) (FCFS) -> ");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 0) {
            printf("%s ", processes[i].name);
        }
    }
    printf("\n");

    printf("CPU-2 que2(priority-1) (SJF) -> ");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 1) {
            printf("%s ", processes[i].name);
        }
    }
    printf("\n");

    printf("CPU-2 que3(priority-2) (RR-q8) -> ");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 2) {
            printf("%s ", processes[i].name);
        }
    }
    printf("\n");

    printf("CPU-2 que4(priority-3) (RR-q16) -> ");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 3) {
            printf("%s ", processes[i].name);
        }
    }
    printf("\n");

    return 0;
}

void fcfs_scheduler(Process* processes, int num_processes, FILE* output_file) {
    Queue cpu1_queue = { .front = 0, .rear = -1 };
    int current_time = 0;

    // Queue up all priority-0 processes
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 0) {
            fprintf(output_file, "Process %s is queued to be assigned to CPU-1.\n", processes[i].name);
            add_process_to_queue(&processes[i], &cpu1_queue);
        }
    }

    // Execute processes in FCFS order
    while (!is_queue_empty(&cpu1_queue)) {
        Process* current_process = remove_process_from_queue(&cpu1_queue);
        fprintf(output_file, "Process %s is assigned to CPU-1.\n", current_process->name);
        current_time += current_process->burst_time;
        fprintf(output_file, "Process %s is completed and terminated.\n", current_process->name);
    }
}

void add_process_to_queue(Process* process, Queue* queue) {
    if (queue->rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full!\n");
        return;
    }
    queue->rear++;
    queue->arr[queue->rear] = process;
}

Process* remove_process_from_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    Process* process = queue->arr[queue->front];
    queue->front++;
    return process;
}

int is_queue_empty(Queue* queue) {
    return (queue->front > queue->rear);
}