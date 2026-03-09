#include <stdio.h>
#include <stdbool.h>
struct Process {
    int pid, at, bt, pr, rt, ct, tat, wt, resp_t;
    bool started;
};
int main() {
    int n, time = 0, completed = 0;
    float total_tat = 0, total_wt = 0, total_resp_t = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\nArrival Time: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].started = false;
    }
    while (completed < n) {
        int index = -1;
        int highest_pr = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].pr < highest_pr) {
                highest_pr = p[i].pr;
                index = i;
            }
        }
        if (index != -1) {
            if (!p[index].started) {
                p[index].resp_t = time - p[index].at;
                total_resp_t += p[index].resp_t;
                p[index].started = true;
            }
            p[index].rt--;
            time++;
            if (p[index].rt == 0) {
                completed++;
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                total_tat += p[index].tat;
                total_wt += p[index].wt;
            }
        } else {
            time++;
        }
    }
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt, p[i].resp_t);
    }
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Response Time = %.2f\n", total_resp_t / n);
    return 0;
}