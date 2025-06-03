/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/03 16:40:06 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_ctrl_c(t_shell *data)
{
	if (g_sig == SIGINT && data->prog_status == 0)
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
	char	*message;
	int		first;

	if (data->prompt.prompt && ft_strlen(data->prompt.prompt) < 100)
		message = data->prompt.prompt;
	else
		message = PROMPT_DEFAULT;
	first = 1;
	while (true)
	{
		data->prompt.user_input = prompt_line(data, message);
		if (g_sig != SIGINT)
			break ;
		if (first)
			printf("\n");
		data->nb_line += 1;
		first = 0;
	}
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
	ft_readline(data);
	exit_status_ctrl_c(data);
	data->prog_status = 0;
	if (data->prompt.user_input == NULL)
		exit_shell(data);
	if (data->prompt.user_input[0] == '\0')
		return (FAIL);
	save_history(data);
	if (valid_input(data))
	{
		free(data->prompt.user_input);
		data->prompt.user_input = NULL;
		return (FAIL);
	}
	return (SUCCESS);
}
