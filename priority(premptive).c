#include <stdio.h>

struct Process {
    int id, at, bt, priority, remaining_bt, ct, tat, wt;
};

int main() {
    int n, completed = 0, current_time = 0, min_priority = 9999;
    int shortest = -1;
    int check = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival, Burst, Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].remaining_bt = p[i].bt;
    }

    while (completed != n) {
        // Find process with highest priority among arrived processes
        shortest = -1;
        min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_bt > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            current_time++;
            continue;
        }

        // Execute for 1 unit
        p[shortest].remaining_bt--;

        if (p[shortest].remaining_bt == 0) {
            completed++;
            check = 0;
            p[shortest].ct = current_time + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
        current_time++;
    }

    printf("\nID\tWT\tTAT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", p[i].id, p[i].wt, p[i].tat);

    return 0;
}
