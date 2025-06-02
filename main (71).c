#include <stdio.h>
//sjf
#define MAX 10
#define INF 9999

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int finished;
} Process;

void sjf(Process p[], int n) {
    int current_time = 0, completed = 0;
    
    while (completed < n) {
        int idx = -1;
        int min_burst = INF;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].finished) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
                else if (p[i].burst_time == min_burst) {
                   
                    if(p[i].arrival_time < p[idx].arrival_time) idx=i;
                }
            }
        }
        
        if (idx == -1) {
            current_time++;
            continue;
        }
        
        p[idx].start_time = current_time;
        p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
        current_time += p[idx].burst_time;
        p[idx].completion_time = current_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        p[idx].finished = 1;
        completed++;
    }
}

int main() {
    Process p[MAX];
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
      
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].finished = 0;
    }
    
    sjf(p, n);
    
    int total_wt = 0, total_tat = 0, total_rt = 0;
    
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
    printf(" response time: %.2f\n", (float)total_rt / n);
    
    return 0;
}
  