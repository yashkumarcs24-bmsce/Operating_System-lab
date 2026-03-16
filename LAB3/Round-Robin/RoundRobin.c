#include <stdio.h>
#include <string.h>
#define MAX 10
#define QUEUE_SIZE (MAX * 10)
typedef struct {
    int pid,at,bt,rt,ct,tat,wt;
} Process;
typedef struct {
    int data[QUEUE_SIZE];
    int front;
    int rear;
} Queue;
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}
int isEmpty(Queue *q) {
    return q->front == q->rear;
}
void enqueue(Queue *q, int val) {
    q->data[q->rear++] = val;
}
int dequeue(Queue *q) {
    return q->data[q->front++];
}
void addArrivals(Process procs[], int n, Queue *q, int inQueue[], int currentTime) {
    for (int i = 0; i < n; i++) {
        if (!inQueue[i] && procs[i].rt > 0 && procs[i].at <= currentTime) {
            enqueue(q, i);
            inQueue[i] = 1;
        }
    }
}

int main() {
    Process procs[MAX];
    Queue readyQueue;
    int inQueue[MAX];
    int n, tq;
    int completed = 0, time = 0;
    printf("=== Round Robin CPU Scheduling ===\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &procs[i].at, &procs[i].bt);
        procs[i].rt = procs[i].bt;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    initQueue(&readyQueue);
    memset(inQueue, 0, sizeof(inQueue));
    addArrivals(procs, n, &readyQueue, inQueue, time);
    printf("\nGantt Chart:\n|");
    while (completed < n) {
        if (isEmpty(&readyQueue)) {
            time++;
            addArrivals(procs, n, &readyQueue, inQueue, time);
            continue;
        }
        int idx = dequeue(&readyQueue);
        Process *p = &procs[idx];
        if (p->rt > tq) {
            printf(" P%d |", p->pid);
            time    += tq;
            p->rt   -= tq;
            addArrivals(procs, n, &readyQueue, inQueue, time);
            enqueue(&readyQueue, idx);
        } else {
            printf(" P%d |", p->pid);
            time   += p->rt;
            p->rt   = 0;
            p->ct   = time;
            completed++;
            addArrivals(procs, n, &readyQueue, inQueue, time);
        }
    }
    printf("\n\n");
    float totalTAT = 0, totalWT = 0;
    printf("%-8s %-8s %-8s %-8s %-8s %-8s\n",
           "Process", "AT", "BT", "CT", "TAT", "WT");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        procs[i].tat = procs[i].ct - procs[i].at;
        procs[i].wt  = procs[i].tat - procs[i].bt;
        totalTAT    += procs[i].tat;
        totalWT     += procs[i].wt;
        printf("P%-7d %-8d %-8d %-8d %-8d %-8d\n",
               procs[i].pid, procs[i].at, procs[i].bt,
               procs[i].ct,  procs[i].tat, procs[i].wt);
    }
    printf("--------------------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
    printf("Average Waiting Time    : %.2f\n", totalWT  / n);
    return 0;
}
