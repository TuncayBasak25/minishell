/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 07:33:37 by rel-hass         ###   ########.fr       */
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
	valid_input(data);
	return (SUCCESS);
}
