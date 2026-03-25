#include <stdio.h>

int main() {
    int n, i, time = 0, remain, quantum;
    int burst[20], remaining[20];
    int waiting_time = 0, turnaround_time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    printf("Enter burst times:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];  
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");

    int flag;
    for(time = 0, i = 0; remain != 0; ) {
        if(remaining[i] <= quantum && remaining[i] > 0) {
            time += remaining[i];
            remaining[i] = 0;
            flag = 1;
        } 
        else if(remaining[i] > 0) {
            remaining[i] -= quantum;
            time += quantum;
            flag = 0;
        }

        if(remaining[i] == 0 && flag == 1) {
            remain--;
            printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst[i],
                   time, time - burst[i]);
            waiting_time += time - burst[i];
            turnaround_time += time;
        }

        if(i == n - 1)
            i = 0;
        else
            i++;
    }

    printf("\nAverage Turnaround Time = %.2f",
           (float)turnaround_time / n);
    printf("\nAverage Waiting Time = %.2f\n",
           (float)waiting_time / n);

    return 0;
}