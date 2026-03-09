#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turnaround_time;
	int completion_time;  
	int response_time;
} Process;

static void sort_by_arrival(Process *procs, int n)
{
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - 1 - i; ++j) {
			if (procs[j].arrival_time > procs[j+1].arrival_time) {
				Process tmp = procs[j];
				procs[j] = procs[j+1];
				procs[j+1] = tmp;
			}
		}
	}
}
static void calculate_times(Process *procs, int n)
{
	int current_time = 0;
	double total_waiting = 0.0;
	double total_turnaround = 0.0;
	for (int i = 0; i < n; ++i) {
		if (current_time < procs[i].arrival_time)
			current_time = procs[i].arrival_time;
		procs[i].response_time = current_time - procs[i].arrival_time;
		procs[i].waiting_time = procs[i].response_time;
		procs[i].completion_time = current_time + procs[i].burst_time;
		procs[i].turnaround_time = procs[i].completion_time - procs[i].arrival_time;
		current_time = procs[i].completion_time;
		total_waiting += procs[i].waiting_time;
		total_turnaround += procs[i].turnaround_time;
	}
	printf("\n%-5s %-10s %-7s %-7s %-12s %-10s %-12s %-10s\n", "PID", "Arrival", "Burst", "Start", "Completion", "Waiting", "Turnaround", "Response");
	printf("================================================================================\n");
	for (int i = 0; i < n; ++i) {
		int start_time = procs[i].completion_time - procs[i].burst_time;
		printf("%-5d %-10d %-7d %-7d %-12d %-10d %-12d %-10d\n",
			   procs[i].pid,
			   procs[i].arrival_time,
			   procs[i].burst_time,
			   start_time,
			   procs[i].completion_time,
			   procs[i].waiting_time,
			   procs[i].turnaround_time,
			   procs[i].response_time);
	}
	printf("\nAverage Waiting Time    = %.2f\n", total_waiting / n);
	printf("Average Turnaround Time = %.2f\n", total_turnaround / n);
}
int main(void)
{
	int n;
	Process procs[MAX_PROCESSES];
	printf("Enter number of processes: ");
	if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) {
		fprintf(stderr, "Invalid number of processes (1-%d)\n", MAX_PROCESSES);
		return 1;
	}
	for (int i = 0; i < n; ++i) {
		procs[i].pid = i + 1;
		printf("Enter arrival time and burst time for process %d: ", procs[i].pid);
		if (scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time) != 2) {
			fprintf(stderr, "Invalid input\n");
			return 1;
		}
	}
	sort_by_arrival(procs, n);
	calculate_times(procs, n);
	return 0;
}