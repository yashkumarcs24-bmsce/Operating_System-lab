#include <stdio.h>
struct Process {
    int pid, at, bt, ct, tat, wt, completed;
};
int main() {
    int n, time = 0, completed = 0, min_bt, index;
    float total_tat = 0, total_wt = 0;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++){
        printf("Process %d Arrival Time: ",i+1);
        scanf("%d",&p[i].at);
        printf("Process %d Burst Time: ",i+1);
        scanf("%d",&p[i].bt);

        p[i].pid=i+1;
        p[i].completed=0;
    }
    while(completed!=n){
        min_bt=9999;
        index=-1;
        for(int i=0;i<n;i++){
            if(p[i].at<=time && p[i].completed==0){
                if(p[i].bt<min_bt){
                    min_bt=p[i].bt;
                    index=i;
                }
            }
        }
        if(index!=-1){
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;
            total_tat+=p[index].tat;
            total_wt+=p[index].wt;
            p[index].completed=1;
            completed++;
        }
        else
            time++;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    printf("\nAverage Turnaround Time = %.2f",total_tat/n);
    printf("\nAverage Waiting Time = %.2f",total_wt/n);
}
