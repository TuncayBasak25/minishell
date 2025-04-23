/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/01 11:51:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((hot)) RESULT	simple_command(char *cmd, t_i32 start, t_i32 end, char **envp)
{
	pid_t	pid;
	char	*tmp;
	char	**command;
	char	*path;
	char	**paths;

	tmp = ft_substr(cmd, start, end - start);
	if (!tmp)
		return (FAIL);
	command = ft_split(tmp, ' ');
	free(tmp);
	if (!command)
		return (FAIL);
	paths = find_path(envp);
	path = find_custom_path(command[0], paths);
	free_tab(paths);
	pid = fork();
	if (pid == -1)
	{
		command = free_tab(command);
		return (FAIL);
	}
	if (pid == 0)
	{
		if (execve(path, command, envp) == -1)
		{
			ft_putstr_fd(WHITE"minishell: command not found: ", 2);
			ft_putstr_fd(*command, 2);
			ft_putstr_fd("\n"RESET, 2);
			command = free_tab(command);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	free_tab(command);
	return (SUCCESS);
}
