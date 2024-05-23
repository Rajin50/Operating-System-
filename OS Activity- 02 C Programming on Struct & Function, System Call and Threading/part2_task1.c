#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("myfile_x", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char input[100];
    ssize_t bytes;

    printf("Enter strings to the file:\n");

    while (1) {
        printf("Enter string: ");
        fgets(input, 100, stdin);

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "-1") == 0)
            break;

        bytes = write(fd, input, strlen(input));
        if (bytes == -1) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }
        write(fd, "\n", 1);
    }

    close(fd);
    printf("Strings successfully written in the file\n");

    return 0;
}

