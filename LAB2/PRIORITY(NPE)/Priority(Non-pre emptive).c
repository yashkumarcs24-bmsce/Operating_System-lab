#include <stdio.h>
struct Process {
    int pid, at, bt, pr, ct, tat, wt, rt, completed;
};
int main() {
    int n, time=0, completed=0, highest_pr, index;
    float avg_tat=0, avg_wt=0, avg_rt=0;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++){
        printf("\nProcess %d:\n", i+1);
        printf("Arrival Time: ");
        scanf("%d",&p[i].at);
        printf("Burst Time: ");
        scanf("%d",&p[i].bt);
        printf("Priority: ");
        scanf("%d",&p[i].pr);
        p[i].pid=i+1;
        p[i].completed=0;
    }
    while(completed<n){
        highest_pr=9999;
        index=-1;
        for(int i=0;i<n;i++){
            if(p[i].at<=time && p[i].completed==0){
                if(p[i].pr<highest_pr){
                    highest_pr=p[i].pr;
                    index=i;
                }
            }
        }
        if(index!=-1){
            p[index].rt = time - p[index].at;
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;
            avg_tat+=p[index].tat;
            avg_wt+=p[index].wt;
            avg_rt+=p[index].rt;
            p[index].completed=1;
            completed++;
        }
        else {
            time++;
        }
    }
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\nAverage Turnaround Time = %.2f",avg_tat/n);
    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Response Time = %.2f\n",avg_rt/n);
    return 0;
}