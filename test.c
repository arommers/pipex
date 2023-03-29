#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	x;
	int	y;
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[0]);
		x = 9;
		if (write(fd[1], &x, sizeof(int)) == -1)
			return (2);
		close(fd[1]);
	}
	else
	{
		printf("test\n");
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (3);
		y = y * 3;
		close(fd[0]);
		printf("y received from child: %d\n", y);
	}
	return (0);
}

