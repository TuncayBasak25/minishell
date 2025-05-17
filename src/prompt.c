/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/17 15:24:13 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

RESULT	prompt_handling(t_shell *data)
{
	build_prompt(&data->prompt, data->env, data->env_len);
	signal(SIGINT, sigint_prompt);
	data->prompt.user_input = readline(data->prompt.prompt);
	g_sig = 0;
	signal(SIGINT, sigint_exec);
	if (!data->prompt.user_input)
		return (FAIL);
	if (data->prompt.user_input && data->prompt.user_input[0])
		add_history(data->prompt.user_input);
	if (valid_input(data))
	{
		free(data->prompt.user_input);
		data->prompt.user_input = NULL;
		return (FAIL);
	}
	else
		data->prompt.user_input = \
			expand_variables(data, data->prompt.user_input, data->env_len);
	return (SUCCESS);
}
