/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/17 14:25:13 by tbasak           ###   ########.fr       */
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

int	g_sig = 0;

void	sigquit_handler(sigid)
{
	(void)sigid;
	printf("Hey");
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	data = (t_shell){0};
	data.env = copy_env(&data, envp);
	up_shlvl(&data, data.env, data.env_len);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (!read_and_parse_input(&data))
			exec(&data, data.cmd_group.cmd_list);
		free_shell(&data, 0);
	}
	return (0);
}
