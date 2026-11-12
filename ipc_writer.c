#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "mypipe"

int main()
{
    int fd, i = 0;
    char str[200], ch;

    mkfifo(FIFO_NAME, 0644);
    printf("Pipe created.\n");
    printf("Enter your message (press @ to finish):\n");

    while ((ch = fgetc(stdin)) != '@') {
        if (i < 199)
            str[i++] = ch;
    }
    str[i] = '\0';

    fd = open(FIFO_NAME, O_WRONLY);
    write(fd, str, strlen(str) + 1);
    close(fd);
    return 0;
}
