 #include <stdio.h>

struct Process {
    int id, at, bt, rt, q, wt, tat, rt_val;
    int completed, first_execution_done;
};

int main() {
    int n, i, time = 0, completed_count = 0, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for(i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d:\n", i + 1);
        printf("  Arrival Time: "); scanf("%d", &p[i].at);
        printf("  Burst Time: ");   scanf("%d", &p[i].bt);
        printf("  Queue (1:RR, 2:SJF, 3:FCFS): "); scanf("%d", &p[i].q);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
        p[i].first_execution_done = 0;
    }
    printf("\nEnter Time Quantum for Q1 (RR): ");
    scanf("%d", &tq);
    printf("\nGantt Chart: ");
    while(completed_count < n) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(p[i].q == 1 && p[i].at <= time && p[i].rt > 0) {
                found = 1;
                if(!p[i].first_execution_done) {
                    p[i].rt_val = time - p[i].at;
                    p[i].first_execution_done = 1;
                }

                int execute_time = (p[i].rt > tq) ? tq : p[i].rt;
                printf("P%d ", p[i].id);
                time += execute_time;
                p[i].rt -= execute_time;

                if(p[i].rt == 0) {
                    p[i].completed = 1;
                    p[i].tat = time - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed_count++;
                }
                break; 
            }
        }
        if(found) continue;
        int shortest = -1;
        for(i = 0; i < n; i++) {
            if(p[i].q == 2 && p[i].at <= time && p[i].rt > 0) {
                if(shortest == -1 || p[i].bt < p[shortest].bt) {
                    shortest = i;
                }
            }
        }
        if(shortest != -1) {
            if(!p[shortest].first_execution_done) {
                p[shortest].rt_val = time - p[shortest].at;
                p[shortest].first_execution_done = 1;
            }
            printf("P%d ", p[shortest].id);
            time += p[shortest].rt;
            p[shortest].rt = 0;
            p[shortest].completed = 1;
            p[shortest].tat = time - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            completed_count++;
            continue;
        }
        int first = -1;
        for(i = 0; i < n; i++) {
            if(p[i].q == 3 && p[i].at <= time && p[i].rt > 0) {
                if(first == -1 || p[i].at < p[first].at) {
                    first = i;
                }
            }
        }

        if(first != -1) {
            if(!p[first].first_execution_done) {
                p[first].rt_val = time - p[first].at;
                p[first].first_execution_done = 1;
            }
            printf("P%d ", p[first].id);
            time += p[first].rt;
            p[first].rt = 0;
            p[first].completed = 1;
            p[first].tat = time - p[first].at;
            p[first].wt = p[first].tat - p[first].bt;
            completed_count++;
            continue;
        }
        if(!found) time++;
    }
    printf("\n\nPID\tQ\tAT\tBT\tWT\tTAT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].q, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].rt_val);
    }
    return 0;
}