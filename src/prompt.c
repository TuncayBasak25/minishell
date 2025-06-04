/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/02 13:46:59 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_ctrl_c(t_shell *data)
{
	if (g_sig == 2 && data->prog_status == 0)
	{
		data->exit_status = 130;
		data->prev_status_is_ctrl_c = true;
	}
	else
		data->prev_status_is_ctrl_c = false;
	g_sig = 0;
}

void	ft_readline(t_shell *data)
{
	if (data->test_mode == true)
		data->prompt.user_input = readline("");
	else if (data->prompt.prompt && ft_strlen(data->prompt.prompt) < 100)
		data->prompt.user_input = readline(data->prompt.prompt);
	else
		data->prompt.user_input = readline(PROMPT_DEFAULT);
	if (data->prog_status == 0)
	{
		data->nb_line += data->nb_line_heredoc + 1;
		data->nb_line_heredoc = 0;
	}
	else if (data->prog_status == 1)
		data->nb_line += 1;
}

int	prompt_handling(t_shell *data)
{
	build_prompt(&data->prompt, data->env, data->env_len);
	signal(SIGINT, sigint_prompt);
	ft_readline(data);
	exit_status_ctrl_c(data);
	data->prog_status = 0;
	signal(SIGINT, sigint_exec);
	if (!data->prompt.user_input)
		exit_shell(data);
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
	return (SUCCESS);
}
