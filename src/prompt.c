/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/03 19:38:56 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

RESULT	prompt_handling(t_shell *data)
{
	build_prompt(&data->prompt, data->env);
	data->prompt.user_input.chars = readline(data->prompt.prompt);
	if (!data->prompt.user_input.chars)
		return (FAIL);
	if (data->prompt.user_input.chars && data->prompt.user_input.chars[0])
		add_history(data->prompt.user_input.chars);
	if (valid_input(data))
	{
		free(data->prompt.user_input.chars);
		data->prompt.user_input.chars = NULL;
		return (FAIL);
	}
	else
		data->prompt.user_input.chars = \
			expand_variables(data->prompt.user_input.chars);
	return (SUCCESS);
}
