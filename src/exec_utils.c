/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:00:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/14 18:41:06 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_missing_file(t_cmd **cmds)
{
	if (((*cmds)->infile && access((*cmds)->infile, F_OK) == -1))
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd((*cmds)->infile, 2);
		ft_putstr_fd(": No such file or directory\n"RESET, 2);
	}
}
