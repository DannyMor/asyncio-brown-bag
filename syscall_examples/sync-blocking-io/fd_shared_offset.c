#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512 * 5 // typical file block (not page)

int open_and_read(int file_offset)
{
    int fd;
    char buffer[BUFFER_SIZE];
    const char file_name[] = "brown_bag_1.txt";

    fd = open(file_name, O_RDWR);

    if (fd == -1)
    {
        printf("failed to open our brown bag\r\n");
        return 1;
    }
    
    lseek(fd, file_offset, SEEK_SET);
    int num_of_bytes_read = read(fd, buffer, BUFFER_SIZE);
    
    printf("the partial file content is: %s\r\n", buffer);
    // close(fd); <- don't close the file descirptor to show that the process fd table is growing 
    return fd;
}

int main(int argc, char const *argv[])
{
    int fds_count = 3;
    int fds[fds_count];
    int offset_coef = 5; // this is just for the sake of the example - we know the max offset this coefficient will produce is 10 - which is less than the max bytes read so it's "safe"
    for (int i = 0; i < 3; i++)
    {
        int fd = open_and_read(offset_coef*i);
        fds[i] = fd;
    }

    // file descriptors 0, 1 and 2 are already in the fd table and preserved for stdin, stdout and stderr (respectivly) so our count will start from 3
    for (int i = 0; i < fds_count; i++){
        int fd = fds[i];
        printf("file descriptor no. is: %d\r\n", fd);
        close(fd); // close after reading from the different offsets
    }
    
    return 0;
}