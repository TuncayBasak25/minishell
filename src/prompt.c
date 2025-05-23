/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/23 19:26:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_history(t_shell *data)
{
	int	fd;

	fd = open(TMP_HISTORY, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (add_history(data->prompt.user_input));
	add_history(data->prompt.user_input);
	write(fd, data->prompt.user_input, ft_strlen(data->prompt.user_input));
	write(fd, "\n", 1);
	close(fd);
}

void	exit_status_ctrl_c(t_shell *data)
{
	if (g_sig == 2)
	{
		data->exit_status = 130;
		data->prev_status_is_ctrl_c = true;
	}
	else
		data->prev_status_is_ctrl_c = false;
	g_sig = 0;
}

RESULT	prompt_handling(t_shell *data)
{
	build_prompt(&data->prompt, data->env, data->env_len);
	signal(SIGINT, sigint_prompt);
	data->prompt.user_input = readline(data->prompt.prompt);
	exit_status_ctrl_c(data);
	signal(SIGINT, sigint_exec);
	if (!data->prompt.user_input)
	{
		free_shell(data, 1);
		exit(data->exit_status);
	}
	if (!data->prompt.user_input[0])
		return (FAIL);
	if (data->prompt.user_input && data->prompt.user_input[0])
		save_history(data);
	if (valid_input(data))
	{
		free(data->prompt.user_input);
		data->prompt.user_input = NULL;
		return (FAIL);
	}
	data->prompt_len_expanded = calc_expanded_length(data->prompt.user_input, \
		data->env, data->exit_status);
	data->prompt.user_input = expand_variables(data, data->prompt.user_input);
	return (SUCCESS);
}
