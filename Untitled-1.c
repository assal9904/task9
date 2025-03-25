#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 typedef struct 
 {
    int process_id;
    int burst_time;
    int arrival_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int start_time;
    int is_completed;
 }Process;
 

float FCFS(Process processes[], int n){
    int current_time = 0;
    int total_waiting_time = 0;
    for(int i =0; i< n; i++){
        if (current_time < processes[i].arrival_time){
            current_time = processes[i].arrival_time;
        }
        processes[i].start_time = current_time;
        processes[i].completion_time = processes[i].start_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        printf("Process %d - Waiting Time: %d\n", processes[i].process_id, processes[i].waiting_time);
        current_time = processes[i].completion_time;
    }
    return total_waiting_time / n;
}

float SJF(Process processes[], int n){
    int current_time = 0;
    float total_waiting_time = 0;
    int completed = 0;
    for (int i = 0; i < n; i++) {
        processes[i].is_completed = 0;
        processes[i].start_time = -1;
        processes[i].completion_time = -1;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
    printf("SJF Scheduling:\n");


    while(completed < n ){
        int shortest_job = -1;
        int shortest_burst_time = INT_MAX;
        for(int i =0; i< n; i++){
            if(!processes[i].is_completed && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst_time){
                shortest_job = i;
                shortest_burst_time = processes[i].burst_time;
            }
        }
            if(shortest_job != -1){
                Process *p = &processes[shortest_job];
                p->start_time = current_time;
                p->completion_time = current_time + p->burst_time;
                p->turnaround_time = p->completion_time - p->arrival_time;
                p->waiting_time = p->turnaround_time - p->burst_time;
                p->is_completed = 1;
            
            total_waiting_time += p->waiting_time;
            current_time = p->completion_time;
            completed++;
                
            } else{
                int next_arrival = INT_MAX;
                for(int i = 0; i<n;i++){
                    if (!processes[i].is_completed && processes[i].arrival_time > current_time){
                        next_arrival = (processes[i].arrival_time < next_arrival) ? 
                                    processes[i].arrival_time : next_arrival;
                    }
                }
            if(next_arrival != INT_MAX)
            {
                current_time = next_arrival;
            } else{
                break;
            }
        }
    }
            
        
        
    return total_waiting_time / n;
}

float round_robin(Process processes[], int n){
    int current_time = 0;
    int completed = 0;
    float total_waiting_time = 0;
    int *remaining_burst_time = (int *)malloc(n * sizeof(int));
    int quantum = 2;
    for (int i = 0; i<n;i++){
        remaining_burst_time[i] = processes[i].burst_time;
       
    }
    printf("round robin scheduling: \n" );
    while (completed < n){
    int processes_executed = 0;
        for (int i =0; i< n;i++){
            if(remaining_burst_time[i] > 0){
                processes_executed = 1;
                if (remaining_burst_time[i] > quantum)
                {
                    
                    remaining_burst_time[i] -= quantum;
                    current_time += quantum;
                } else{
                    current_time += remaining_burst_time[i];
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_waiting_time += processes[i].waiting_time;
                    remaining_burst_time[i] = 0;
                    completed++;
                }
            }
            }
            if (!processes_executed)
            {
                current_time++;
            }
    }
    free(remaining_burst_time);
    return total_waiting_time / n;   
}


int main(){
    int n;
    printf("enter the number of processes: ");
    scanf("%d",&n);
    Process processes[10];
    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i + 1;
        processes[i].start_time = 0; 
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }
   float fcfs = FCFS(processes, n);
   printf("FCFS Average Waiting Time: %.2f\n", fcfs);
    
    float rr = round_robin(processes, n);
    printf("Round Robin Average Waiting Time: %.2f\n", rr);

    float sjf = SJF(processes, n);
    printf("SJF Average Waiting Time: %.2f\n", sjf);
    return 0;
}