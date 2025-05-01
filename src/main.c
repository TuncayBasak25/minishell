/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 10:28:17 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	go_to_head(t_shell *data)
{
	if (!data->cmd_group.cmd_list)
		return ;
	while (data->cmd_group.cmd_list->prev)
		data->cmd_group.cmd_list = data->cmd_group.cmd_list->prev;
}

RESULT	read_and_parse_input(t_shell *data)
{
	if (prompt_handling(data))
		return (FAIL);
	get_input_data(data);
	go_to_head(data);
	return (SUCCESS);
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	init_struct_shell(&data);
	data.env = envp;
	while (1)
	{
		if (read_and_parse_input(&data))
			break ;
		while (data.cmd_group.cmd_list)
			exec(&data);
		printf("line: %s\n", data.prompt.user_input.chars);
		free(data.prompt.user_input.chars);
	}
	return (0);
}
