#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int binary_search(int a[], int n, int key)
{
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] == key)
            return mid;
        if (a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main()
{
    int n, i, key, pos;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Parent PID: %d\n", getpid());
    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        sort(a, n);
        printf("Enter element to search: ");
        scanf("%d", &key);
        pos = binary_search(a, n, key);
        if (pos != -1)
            printf("Found at position %d\n", pos + 1);
        else
            printf("Element not found.\n");
        exit(0);
    }

    sort(a, n);
    printf("Child PID: %d\n", pid);
    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    wait(NULL);
    printf("Child finished. Parent is back.\n");

    printf("\n--- Zombie process ---\n");
    pid = fork();
    if (pid == 0)
        exit(0);
    sleep(2);
    printf("Child %d is a zombie until we wait.\n", pid);
    waitpid(pid, NULL, 0);
    printf("Zombie cleaned up.\n");

    printf("\n--- Orphan process ---\n");
    pid = fork();
    if (pid == 0) {
        sleep(2);
        printf("Orphan PID: %d, new parent PID: %d\n", getpid(), getppid());
        exit(0);
    }
    printf("Parent is exiting. Child will become an orphan.\n");
    exit(0);
}
