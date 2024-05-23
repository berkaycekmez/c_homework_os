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
    Process *arr[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

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