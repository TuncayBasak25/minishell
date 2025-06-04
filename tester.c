/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:53:58 by tbasak            #+#    #+#             */
/*   Updated: 2025/06/04 08:58:25 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 600
#include <pty.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char
*gnl(int fd)
{
	static char	buff[BUFFER_SIZE];
	static int	buff_offset;
	static int	buff_len;
	char	*line;
	char	*tmp;
	int		line_len;
	int		i;

	if (fd == -1)
		return (NULL);
	line = NULL;
	line_len = 0;
	while (line_len == 0 || line[line_len - 1] != '\n')
	{
		if (buff_offset == 0)
		{
			buff_len = read(fd, buff, BUFFER_SIZE);
			if (buff_len == -1)
			{
				free(line);
				return (NULL);
			}
			if (buff_len == 0)
				break ;
		}
		i = buff_offset;
		while (i < buff_len && buff[i++] != '\n')
			continue ;
		tmp = malloc(line_len + i - buff_offset + 1);
		if (tmp == NULL)
		{
			free(line);
			buff_offset = 0;
			return (NULL);
		}
		i = -1;
		while (++i < line_len)
			tmp[i] = line[i];
		free(line);
		line = tmp;
		while (buff_offset < buff_len && (line_len == 0 || line[line_len - 1] != '\n'))
			line[line_len++] = buff[buff_offset++];
		if (buff_offset == buff_len)
			buff_offset = 0;
		line[line_len] = '\0';
	}
	return (line);
}

static char	*ft_itoa(int n)
{
	size_t			index;
	long long int	big;
	char			buff[12];

	buff[11] = '\0';
	index = 10;
	big = (long long int)n;
	if (big < 0)
		big *= -1;
	while (1)
	{
		buff[index--] = '0' + big % 10;
		if (big < 10)
			break ;
		big /= 10;
	}
	if (n < 0)
		buff[index--] = '-';
	return (strdup(buff + index + 1));
}

static void	minishell(const char *tester_pid)
{
	sleep(1);
	execl("/bin/valgrind", \
		"valgrind", \
		"--track-fds=yes", \
		"--leak-check=full", \
		"--show-leak-kinds=all", \
		"--track-origins=yes", \
		"--trace-children=yes", \
		"--suppressions=readline.supp", \
		"-s", \
		"./minishell", \
		tester_pid, \
		NULL);
	perror("execl failed");
	exit(EXIT_FAILURE);
}

static sig_atomic_t	g_sig;

static void	sigusr1(int sigid)
{
	g_sig = sigid;
}

static void	output(int master_fd)
{
	char	buff[BUFFER_SIZE];
	int		buff_len;

	while (1)
	{
		buff_len = read(master_fd, buff, BUFFER_SIZE);
		if (buff_len < 0)
		{
			printf("Read error at output process!\n");
			exit(1);
		}
		write(1, buff, buff_len);
	}
	exit(0);
}

static void	input(int master_fd, int input_fd)
{
	char	*line;
	int		line_len;

	while (1)
	{
		signal(SIGUSR1, sigusr1);
		if (!g_sig)
		{
			usleep(100);
			continue ;
		}
		g_sig = 0;
		line = gnl(input_fd);
		if (!line)
			break ;
		line_len = strlen(line);
		write(master_fd, line, line_len);

	}
	exit(0);
}

int	main(int ac, char **av)
{
	int		input_fd;
	int		master_fd;
	int		pid;
	char	*tester_pid;

	if (ac != 2)
	{
		printf("Provide a input file!\n");
		return (1);
	}
	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
	{
		printf("Faled to open file %s!\n", av[1]);
		return (1);
	}
	tester_pid = ft_itoa(getpid());
	pid = forkpty(&master_fd, NULL, NULL, NULL);
	if (pid == -1)
	{
		perror("forkpty");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		minishell(tester_pid);
	if (fork())
		input(master_fd, input_fd);
	output(master_fd);
	return (0);
}
