/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 00:58:12 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

RESULT	prompt_handling(t_shell *data)
{
	build_prompt(&data->prompt, data->env);
	data->prompt.user_input = readline(data->prompt.prompt);
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
			expand_variables(data->env, data->prompt.user_input);
	return (SUCCESS);
}
