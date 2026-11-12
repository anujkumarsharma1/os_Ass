#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "mypipe"

int main()
{
    int fd, i, chars = 0, words = 0, lines = 0;
    char str[200];

    mkfifo(FIFO_NAME, 0644);
    fd = open(FIFO_NAME, O_RDONLY);
    read(fd, str, sizeof(str));
    close(fd);

    for (i = 0; str[i] != '\0'; i++) {
        chars++;
        if (str[i] == ' ' || str[i] == '\n')
            words++;
        if (str[i] == '\n')
            lines++;
    }
    if (chars > 0 && str[chars - 1] != ' ' && str[chars - 1] != '\n')
        words++;

    printf("Characters: %d\n", chars);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines + 1);
    return 0;
}
