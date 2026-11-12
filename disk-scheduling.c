#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int req[100], n, disk_size, head;
int has_input = 0;

void take_input()
{
    int i;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter request sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    has_input = 1;
}

void sort_arr(int a[], int len)
{
    int i, j, temp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void sstf()
{
    int done[100] = {0};
    int cur = head, total = 0, i, j, nearest, dist, min_dist;
    printf("\nSSTF: %d", cur);
    for (i = 0; i < n; i++) {
        min_dist = INT_MAX;
        nearest = -1;
        for (j = 0; j < n; j++) {
            dist = abs(req[j] - cur);
            if (!done[j] && dist < min_dist) {
                min_dist = dist;
                nearest = j;
            }
        }
        total += min_dist;
        cur = req[nearest];
        done[nearest] = 1;
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement: %d\n", total);
}

void scan()
{
    int a[100], cur = head, total = 0, start = n, i;
    for (i = 0; i < n; i++)
        a[i] = req[i];
    sort_arr(a, n);
    for (i = 0; i < n; i++) {
        if (a[i] >= head) {
            start = i;
            break;
        }
    }
    printf("\nSCAN: %d", cur);
    for (i = start; i < n; i++) {
        total += abs(a[i] - cur);
        cur = a[i];
        printf(" -> %d", cur);
    }
    if (cur != disk_size - 1) {
        total += abs((disk_size - 1) - cur);
        cur = disk_size - 1;
        printf(" -> %d", cur);
    }
    for (i = start - 1; i >= 0; i--) {
        total += abs(a[i] - cur);
        cur = a[i];
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement: %d\n", total);
}

void clook()
{
    int a[100], cur = head, total = 0, start = n, i;
    for (i = 0; i < n; i++)
        a[i] = req[i];
    sort_arr(a, n);
    for (i = 0; i < n; i++) {
        if (a[i] >= head) {
            start = i;
            break;
        }
    }
    printf("\nC-LOOK: %d", cur);
    for (i = start; i < n; i++) {
        total += abs(a[i] - cur);
        cur = a[i];
        printf(" -> %d", cur);
    }
    for (i = 0; i < start; i++) {
        total += abs(a[i] - cur);
        cur = a[i];
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement: %d\n", total);
}

int main()
{
    int ch;
    while (1) {
        printf("\n1. Input\n2. SSTF\n3. SCAN\n4. C-LOOK\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        if (ch == 1) {
            take_input();
        } else if (ch == 2 || ch == 3 || ch == 4) {
            if (!has_input) {
                printf("Enter data first.\n");
                continue;
            }
            if (ch == 2)
                sstf();
            else if (ch == 3)
                scan();
            else
                clook();
        } else if (ch == 5) {
            return 0;
        } else {
            printf("Invalid choice.\n");
        }
    }
}
