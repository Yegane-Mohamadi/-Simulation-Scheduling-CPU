#include <stdio.h>
//fcfs
#define MAX 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

void fcfs(Process p[], int n) {
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;
        
        p[i].start_time = current_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;
        
        current_time += p[i].burst_time;
        
        p[i].completion_time = current_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

int main() {
    Process p[MAX];
    int n;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
       
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }
    
    fcfs(p, n);
    
    int total_wt = 0, total_tat = 0, total_rt = 0;
    
    printf("PID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].completion_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }
    
    printf(" waiting time: %.2f\n", (float)total_wt / n);
    printf(" turnaround time: %.2f\n", (float)total_tat / n);
    printf("response time: %.2f\n", (float)total_rt / n);
    
    return 0;
}
  