/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 12:39:16 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_head(t_shell *data)
{
	if (!data->cmd_group.cmd_list)
		return ;
	while (data->cmd_group.cmd_list->prev)
		data->cmd_group.cmd_list = data->cmd_group.cmd_list->prev;
}

int	read_and_parse_input(t_shell *data)
{
	if (prompt_handling(data))
		return (FAIL);
	get_input_data(data);
	go_to_head(data);
	if (data->heredoc_quit)
		return (FAIL);
	return (SUCCESS);
}

int	g_sig = 0;

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	data = (t_shell){0};
	data.env = copy_env(&data, envp);
	incomplete_env_start(&data, argv[0]);
	secret_path(&data);
	signal(SIGQUIT, SIG_IGN);
	load_history(&data);
	while (1)
	{
		if (!read_and_parse_input(&data))
			exec(&data, data.cmd_group.cmd_list);
		free_shell(&data, 0);
	}
	return (0);
}
