#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024


int main(int argc, char **argv)
{
    int from_fd, to_fd;
	int bytes_read, bytes_write;
	char buffer[BUFFER_SIZE];
	
	// 部分写
	char *ptr = NULL;

    int ret;

    if (3 != argc)
	{
		printf("need from file and to filen!\n");
		exit(0);
	}
 
    from_fd = open(argv[1], O_RDONLY);
	if (-1 == from_fd)
	{
		perror("open from file error!\n");
		exit(-1);
	}
	
	//  因为create所以有第三个参数mode 
	if ((to_fd = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRGRP | S_IRUSR)) == -1)
	{
		perror("open to file error!\n");
		close(from_fd);
		exit(-1);
	}

    while (bytes_read = read(from_fd, buffer, BUFFER_SIZE))
	{
        if (-1 == bytes_read)
		{
			perror("read from file! file copy fail!\n");
			break;
		}
		else if (bytes_read > 0)
		{
			ptr = buffer;

            while (bytes_write = write(to_fd, buffer, bytes_read))
			{
                if (-1 == bytes_write)
				{
					perror("write error! file copy fail!\n");

					// 多重最好goto
					break;
				}        
                else if (bytes_write == bytes_read)
				{
					break;
				}
				else
				{
					bytes_read = bytes_read - bytes_write;
					ptr = ptr + bytes_write;
				}
			}

			if (-1 == bytes_write)
			{
				break;
			}
		}

		
	}

	close(from_fd);
	close(to_fd);

	return 0;
}