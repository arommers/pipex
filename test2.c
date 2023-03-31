/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 11:12:55 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/29 15:37:09 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	pipe1[2];
	int	pipe2[2];
	int	pid;
	int	x;
	int	y;

	if (pipe(pipe1) == -1)
		return (1);
	if (pipe(pipe2) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		//child process
		close(pipe1[0]);
		close(pipe2[1]);
		if (read(pipe2[0], &x, sizeof(x)) == -1)
			return (3);
		printf("received: %d\n", x);
		x = x * 4;
		if (write(pipe1[1], &x, sizeof(x)) == -1)
			return (4);
		printf("Wrote: %d\n", x);
		close(pipe1[1]);
		close(pipe2[0]);
	}
	else
	{
		//parent proces
		close(pipe1[1]);
		close(pipe2[0]);
		srand(time(NULL));
		y = rand() % 10;
		if (write(pipe2[1], &y, sizeof(y)) == -1)
			return (5);
		printf("wrote: %d\n", y);
		if (read(pipe1[0], &y, sizeof(y)) == -1)
			return (6);
		printf("result: %d\n", y);
		close(pipe1[0]);
		close(pipe2[1]);
		wait(NULL);
	}
	return (0);
}
