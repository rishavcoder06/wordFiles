// Task 2: Implementation of CPU scheduling algorithms to find turnaround time and waiting time. 
// a) FCFS b) SJF c) Round Robin (pre-emptive) d) Priority.
#include <stdio.h>
#include <stdbool.h>

struct Process{
    int arrivalTime;
    int burstTime;
    int turnAroundTime;
    int waitingTime;
    int remaining_burstTime;
};

void print(struct Process* p, int n){

    float avgTurnAroundTime = 0;
    float avgWaitingTime = 0;

    printf("Process ArivalTime BurstTime TurnAroundTime WaitingTime \n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t   %d\t\t %d\t\t%d\n",
        i, p[i].arrivalTime, p[i].burstTime, p[i].turnAroundTime, p[i].waitingTime);

        avgTurnAroundTime += p[i].turnAroundTime;
        avgWaitingTime += p[i].waitingTime;
    }
    printf("Average Turn Around Time : %f \n", avgTurnAroundTime); 
    printf("Average Wating Time : %f \n", avgWaitingTime);
}

void FCFS(struct Process* p, int n){
    printf("FCFS Method\n");
    int completionTime = p[0].burstTime-1;
    for(int i=0; i<n; i++){

        p[i].turnAroundTime = completionTime - p[i].arrivalTime;
        if(i<n-1) completionTime += p[i+1].burstTime;

        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
    }
    print(p, n);

}

void roundRobin(struct Process* p, int n, int quantum){
    printf("Round Robin Method\n");
    int remainingTime[n];
    for(int i = 0; i < n; i++){
        remainingTime[i] = p[i].burstTime;
    }
    int t = 0;
    while(1){
        bool done = true;
        for(int i = 0; i < n; i++){
            if(remainingTime[i] > 0){
                done = false;

                if(remainingTime[i] > quantum){
                    t += quantum;
                    remainingTime[i] -= quantum;
                }else{
                    t += remainingTime[i];
                    p[i].waitingTime = t - p[i].burstTime;
                    remainingTime[i] = 0;
                }
            }
        }
        if(done) break;
    }
    for(int i = 0; i < n; i++){
        p[i].turnAroundTime = p[i].burstTime + p[i].waitingTime;
    }
    print(p, n);
}

int main(){
    int n = 4;
    struct Process p[n];
    p[0].arrivalTime = 0; p[0].burstTime = 5;
    p[1].arrivalTime = 1; p[1].burstTime = 3;
    p[2].arrivalTime = 2; p[2].burstTime = 8;
    p[3].arrivalTime = 3; p[3].burstTime = 6;

    // p[0].arrivalTime = 0; p[0].burstTime = 5;
    // p[1].arrivalTime = 1; p[1].burstTime = 4;
    // p[2].arrivalTime = 2; p[2].burstTime = 2;
    // p[3].arrivalTime = 4; p[3].burstTime = 1;

    // FCFS(p, n);

    roundRobin(p, n, 2);

    return 0;
}