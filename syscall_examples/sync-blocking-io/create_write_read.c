#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 80
int main(int argc, char const *argv[])
{
    int fd;
    const char file_name[] = "brown_bag_1.txt";
    char buffer[BUFFER_SIZE];
    char file_content[] = "this is totally blocking and happens synchronically!\0";

    fd = open(file_name, O_RDWR | O_CREAT);

    if (fd == -1)
    {
        printf("failed to open file: %s \r\n", file_name);
        return 1;
    }

    // make it possible to view the file after we create it
    fchmod(fd, S_IRWXO | S_IRWXG | S_IRWXU);

    printf("the file descriptor is: %d \r\n", fd);
    // write to file
    int file_content_size = sizeof(file_content) - 1;
    // write to file using fd
    write(fd, file_content, file_content_size);
    // resetting fd to read from the beginning of the file
    lseek(fd, 0, SEEK_SET);
    // reading from the file
    int num_of_bytes_read = read(fd, buffer, file_content_size);

    printf("number of bytes read from file: %d \n", num_of_bytes_read);

    printf("file content: %s \n", buffer);
    // we need to make sure to clean up and close the file

    close(fd);
    return 0;
}