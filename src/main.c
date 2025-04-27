/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/25 21:42:24 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

RESULT	get_data(t_shell *data)
{
	if (prompt_handling(data))
		return (FAIL);
	if (get_all_command(data))
		return (SUCCESS);
	while (data->cmd_group.cmd_list->prev)
		data->cmd_group.cmd_list = data->cmd_group.cmd_list->prev;
	return (SUCCESS);
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	data.env = envp;
	while (1)
	{
		if (get_data(&data))
			break ;
		while (data.cmd_group.cmd_list)
		{
			printf(BRED"PIPE %d : %s\n"RESET, data.cmd_group.cmd_list->id, data.cmd_group.cmd_list->command[0]);
			if (!ft_strncmp(*data.cmd_group.cmd_list->command, "cd", 2))
				cd(*data.cmd_group.cmd_list->command, &data.prompt);
			else if (ft_strncmp(*data.cmd_group.cmd_list->command, "echo", 4) == 0)
				echo(*data.cmd_group.cmd_list->command, envp);
			else if (ft_strncmp(*data.cmd_group.cmd_list->command, "pwd", 3) == 0)
				pwd();
			else if (ft_strncmp(*data.cmd_group.cmd_list->command, "exit", 4) == 0)
				return (free(data.prompt.user_input.chars), 0);
			else if (simple_command(data.cmd_group.cmd_list, envp))
				continue ;
			data.cmd_group.cmd_list = data.cmd_group.cmd_list->next;
		}
		printf("line: %s\n", data.prompt.user_input.chars);
		free(data.prompt.user_input.chars);
	}
	return (0);
}
