/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/03 16:37:03 by tbasak           ###   ########.fr       */
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

static int	parse_pid(const char *cstr)
{
	int	pid;
	int	mypid;

	if (!cstr)
		return (0);
	pid = 0;
	mypid = getpid();
	while (cstr[0] >= '0' && cstr[0] <= '9')
	{
		pid *= 10;
		pid += cstr[0] - '0';
		if (pid >= mypid)
			return (0);
		cstr++;
	}
	if (cstr[0])
		return (0);
	return ((int)pid);
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	data = (t_shell){0};
	if (argc > 1)
	{
		data.tester_pid = parse_pid(argv[1]);
		if (data.tester_pid == 0)
		{
			printf("Invalid tester pid[%s]!\n", argv[1]);
			return (1);
		}
	}
	data.env = copy_env(&data, envp);
	incomplete_env_start(&data, argv[0]);
	secret_path(&data);
	data.tilde = get_env(data.env, "HOME=", data.env_len);
	load_history(&data);
	while (1)
	{
		if (!read_and_parse_input(&data))
			exec(&data, data.cmd_group.cmd_list);
		free_shell(&data, 0);
	}
	return (0);
}
