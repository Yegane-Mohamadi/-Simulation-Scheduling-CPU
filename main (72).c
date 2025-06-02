#include <stdio.h>
//round bin
#define MAX 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int start_time;
    int first_response;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int finished;
} Process;

void round_robin(Process p[], int n, int quantum) {
    int current_time = 0, completed = 0;
    int mark_first_response[MAX] = {0};
    
    for(int i=0; i<n; i++) {
        p[i].remaining_time = p[i].burst_time;
        p[i].first_response = -1;
        p[i].finished = 0;
    }
    
    while (completed < n) {
        int done_something = 0;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].first_response == -1)
                    p[i].first_response = current_time;
                
                if (p[i].remaining_time > quantum) {
                    current_time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    current_time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completion_time = current_time;
                    p[i].finished = 1;
                    completed++;
                }
                
                done_something = 1;
            }
        }
        
        if (!done_something) {
            current_time++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].first_response - p[i].arrival_time;
    }
}

int main() {
    Process p[MAX];
    int n, quantum;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }
    
    scanf("%d", &quantum);
    
    round_robin(p, n, quantum);
    
    int total_wt = 0, total_tat = 0, total_rt = 0;
    
    printf("PID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
        
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }
    
    printf(" waiting time: %.2f\n", (float)total_wt / n);
    printf(" turnaround time: %.2f\n", (float)total_tat / n);
    printf(" response time: %.2f\n", (float)total_rt / n);
    
    return 0;
}
  