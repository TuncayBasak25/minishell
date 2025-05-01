/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:50:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 08:57:52 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_struct_shell(t_shell *data)
{
	data->env = NULL;
	data->prompt.user_input.chars = NULL;
	data->prompt.user_input.len = 0;
	data->prompt.user_input.buffer.ptr = NULL;
	data->prompt.user_input.buffer.size = 0;
	data->prompt.user = NULL;
	data->prompt.home = NULL;
	data->prompt.pwd = NULL;
	data->prompt.host = NULL;
	data->prompt.prompt = NULL;
	data->cmd_group.count = 0;
	data->cmd_group.cmd_list = NULL;
	data->cmd_group.path = NULL;
}
