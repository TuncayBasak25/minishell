/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:34:54 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 13:12:56 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *data, char **cmds)
{
	char	pwd[1024];

	if (cmds[1] && cmds[1][0] == '-')
	{
		ft_putstr_fd(WHITE"minishell: pwd: -: invalid option\n"RESET, 2);
		data->exit_status = 2;
		return ;
	}
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		data->exit_status = 0;
	}
	else
	{
		perror("getcwd() error");
		data->exit_status = 1;
	}
}
