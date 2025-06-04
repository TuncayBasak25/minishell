/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/04 07:07:38 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*message(t_shell *data)
{
	if (data->prompt.prompt && ft_strlen(data->prompt.prompt) < 100)
		return (data->prompt.prompt);
	return (PROMPT_DEFAULT);
}

void	ft_readline(t_shell *data)
{
	int	first;

	first = !data->heredoc_quit;
	while (true)
	{
		data->prompt.user_input = prompt_line(data, message(data));
		if (g_sig != SIGINT)
			break ;
		if (data->heredoc_unexpected)
			printf("\n\n");
		else if (first)
			printf("\n");
		data->nb_line += 1;
		first = 0;
	}
	data->heredoc_unexpected = false;
	data->heredoc_quit = 0;
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
