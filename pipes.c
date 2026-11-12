#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2], fd, n;
    char filename[100], buffer[100];

    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));
        fd = open(filename, O_RDONLY);
        if (fd < 0) {
            printf("File not found.\n");
            return 1;
        }

        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            write(p2[1], buffer, n);

        close(fd);
        close(p1[0]);
        close(p2[1]);
    } else {
        close(p1[0]);
        close(p2[1]);

        printf("Enter filename: ");
        fflush(stdout);
        scanf("%s", filename);
        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        printf("\nFile contents:\n");
        fflush(stdout);
        while ((n = read(p2[0], buffer, sizeof(buffer))) > 0)
            write(1, buffer, n);

        close(p2[0]);
        wait(NULL);
    }

    return 0;
}
