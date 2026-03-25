 #include <stdio.h>

int main() {
    int n, i, j;
    
    int at[20], bt[20], pr[20], ct[20], wt[20], tat[20];
    int temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

   
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);

        printf("P%d Priority: ", i+1);
        scanf("%d", &pr[i]);
    }

     
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                 
                temp = at[i]; at[i] = at[j]; at[j] = temp;

                 
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;

                
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    
    ct[0] = at[0] + bt[0];

    for(i = 1; i < n; i++) {
        int current_time = ct[i-1];
        int highest_priority_index = i;

       
        for(j = i; j < n; j++) {
            if(at[j] <= current_time) {
                if(pr[j] < pr[highest_priority_index]) {
                    highest_priority_index = j;
                }
            }
        }

         
        if(highest_priority_index != i) {
            temp = at[i]; at[i] = at[highest_priority_index]; at[highest_priority_index] = temp;
            temp = bt[i]; bt[i] = bt[highest_priority_index]; bt[highest_priority_index] = temp;
            temp = pr[i]; pr[i] = pr[highest_priority_index]; pr[highest_priority_index] = temp;
        }

         
        if(ct[i-1] < at[i]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i-1] + bt[i];
        }
    }

     
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

 
    float total_wt = 0, total_tat = 0;

    printf("\nAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}