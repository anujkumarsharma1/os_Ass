#include <stdio.h>

int main()
{
    int max[10][10], alloc[10][10], need[10][10];
    int avail[10], finish[10], safe[10];
    int p, r, i, j, k, count = 0, found;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &r);

    printf("Enter Max matrix:\n");
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Available resources:\n");
    for (j = 0; j < r; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < p; i++) {
        finish[i] = 0;
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    while (count < p) {
        found = 0;
        for (i = 0; i < p; i++) {
            if (finish[i])
                continue;

            for (j = 0; j < r; j++) {
                if (need[i][j] > avail[j])
                    break;
            }

            if (j == r) {
                for (k = 0; k < r; k++)
                    avail[k] += alloc[i][k];
                safe[count++] = i;
                finish[i] = 1;
                found = 1;
                printf("P%d executed\n", i);
            }
        }
        if (!found)
            break;
    }

    if (count == p) {
        printf("\nSAFE STATE\nSafe sequence: ");
        for (i = 0; i < p; i++)
            printf("P%d ", safe[i]);
        printf("\n");
    } else {
        printf("\nUNSAFE STATE\n");
    }

    return 0;
}
