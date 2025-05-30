#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "include/includes.h"

int	str_len(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

typedef struct s_program
{
	int	pid;
	int	inp;
	int	out;
	int	err;
}		t_program;

t_program	spawn_program(char *name, char **envp)
{
	char	*av[2];
	int		pid;
	int		inp_pipe[2];
	int		out_pipe[2];
	int		err_pipe[2];

	pipe(inp_pipe);
	pipe(out_pipe);
	pipe(err_pipe);
	pid = fork();
	if (pid == 0)
	{
		close(inp_pipe[1]);
		close(out_pipe[0]);
		close(err_pipe[0]);
		dup2(inp_pipe[0], 0);
		dup2(out_pipe[1], 1);
		dup2(err_pipe[1], 2);
		close(inp_pipe[0]);
		close(out_pipe[1]);
		close(err_pipe[1]);
		av[0] = name;
		av[1] = NULL;
		execve(name, av, envp);
		printf("Execve failed!\n");
		exit(1);
	}
	close(inp_pipe[0]);
	close(out_pipe[1]);
	close(err_pipe[1]);
	return ((t_program){pid, inp_pipe[1], out_pipe[0], err_pipe[0]});
}

typedef struct s_program_result
{
	int	out;
	int	err;
	int	status;
}		t_program_result;

t_program_result	test_shell(t_program shell, char *input)
{
	int	status;

	write(shell.inp, input, str_len(input));
	close(shell.inp);
	waitpid(shell.pid, &status, 0);
	return ((t_program_result){shell.out, shell.err, status});
}

void	fd_to_file(int fd, char *filepath)
{
	int	file_fd;

	file_fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if (file_fd == -1)
	{
		printf("Failed to open %s\n", filepath);
		return ;
	}
	char	buff[1024];
	int		rd;

	rd = 1;
	while (rd)
	{
		rd = read(fd, buff, 1024);
		if (rd == -1)
			return ;
		write(file_fd, buff, rd);
	}
}

void	file_append(char *filepath, char *str)
{
	int	fd = open(filepath, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
	if (fd == -1)
		return ;
	write(fd, str, str_len(str));
}

void	compare_command_flow(char *command_flow, char **envp)
{
	t_program			bash;
	t_program			mini;
	t_program_result	bash_result;
	t_program_result	mini_result;

	bash = spawn_program("/bin/bash", envp);
	bash_result = test_shell(bash, command_flow);
	mini = spawn_program("./minishell", envp);
	mini_result = test_shell(mini, command_flow);

	if (bash_result.status != mini_result.status)
	{
		printf("FLOW: %s\n", command_flow);
		printf("Exit status diff: bash(%d) != minishell(%d)\n", bash_result.status, mini_result.status);
	}
	int	line_number = 0;
	while (1)
	{
		char	*bash_line = get_next_line(bash_result.out);
		char	*mini_line = get_next_line(mini_result.out);

		file_append("bash_out", bash_line);
		file_append("mini_out", mini_line);
		if ((bash_line && !mini_line) || (!bash_line && mini_line) || (bash_line && mini_line && strcmp(bash_line, mini_line)))
		{
			printf("FLOW: %s\n", command_flow);
			printf("STDOUT DIFF AT LINE [%d]\n\n", line_number);
			break ;
		}
		free(bash_line);
		free(mini_line);
		if (!bash_line && !mini_line)
			break ;
		line_number++;
	}
	line_number = 0;
	while (1)
	{
		char	*bash_line = get_next_line(bash_result.err);
		char	*mini_line = get_next_line(mini_result.err);

		file_append("bash_err", bash_line);
		file_append("mini_err", mini_line);
		if ((bash_line && !mini_line) || (!bash_line && mini_line) || (bash_line && mini_line && strcmp(bash_line, mini_line)))
		{
			printf("FLOW: %s\n", command_flow);
			printf("STDERR DIFF AT LINE [%d]\n\n", line_number);
			break ;
		}
		free(bash_line);
		free(mini_line);
		if (!bash_line && !mini_line)
			break ;
		line_number++;
	}
}

char	*get_next_double_line(int fd)
{
	static char	buff[1024];
	static int	buff_offset;
	static int	buff_len;
	char		*line;
	char		*tmp;
	int			line_len;
	int			i;

	if (fd == -1)
		return (NULL);
	line = NULL;
	line_len = 0;
	while (line_len == 0 || line[line_len] == '\n')
	{
		if (buff_offset == 0)
		{
			buff_len = read(fd, buff, 1024);
			if (buff_len == -1)
			{
				free(line);
				return (NULL);
			}
			if (buff_len == 0)
				break ;
		}
		i = buff_offset - 1;
		while (++i < buff_len)
		{
			if (i == 0)
				continue ;
			if (buff[i - 1] == '\n' && buff[i] == '\n')
				break ;
		}
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
		while (buff_offset < buff_len)
		{
			if (line[line_len - 1] == '\n' && buff[buff_offset] == '\n')
			{
				buff_offset++;
				break ;
			}
			line[line_len++] = buff[buff_offset++];
		}
		if (buff_offset == buff_len)
			buff_offset = 0;
		line[line_len] = '\0';
	}
	return (line);
}

int main(int ac, char **av, char **envp)
{
	if (ac < 2)
	{
		printf("Provide a command flow file\n");
		return (1);
	}
	int	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Cannot open %s\n", av[1]);
		return (1);
	}
	open("bash_out", O_CREAT | O_TRUNC, S_IRWXU);
	open("mini_out", O_CREAT | O_TRUNC, S_IRWXU);
	open("bash_err", O_CREAT | O_TRUNC, S_IRWXU);
	open("mini_err", O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		char	*flow = get_next_double_line(fd);
		if (!flow)
			break ;
		compare_command_flow(flow, envp);
		free(flow);
	}
}
