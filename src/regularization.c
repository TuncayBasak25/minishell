/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regularization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:09:27 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/04 07:41:50 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reduce_whitespace(const char *str)
{
	char	*result;
	int		in_space;
	t_utils	u;

	if (!str)
		return (NULL);
	result = (char *) ft_calloc(ft_strlen(str) + 1, sizeof(char));
	u.i = -1;
	u.j = 0;
	in_space = 0;
	while (result && str[++u.i])
	{
		if (is_whitespace(str[u.i]))
		{
			if (!in_space)
				result[u.j++] = ' ';
			in_space = 1;
		}
		else
		{
			result[u.j++] = str[u.i];
			in_space = 0;
		}
	}
	return (result);
}

void	regularization(t_shell *data, t_cmd *cmd, char **command)
{
	int		i;
	t_utils	utils;

	i = -1;
	if (!cmd || !cmd->command || !command)
		return ;
	while (cmd->command[++i])
	{
		if (!command[i])
			return ;
		if (!find_char(command[i], '\"') && !find_char(command[i], '\'') && \
		find_char(command[i], '$') && (find_char(cmd->command[i], ' ') || \
		find_char(cmd->command[i], '\t') || !cmd->command[i][0]))
		{
			command[i] = expand_variables(data, command[i]);
			if (ft_strcmp(cmd->command[0], "export"))
				utils.ptr = reduce_whitespace(command[i]);
			else
				utils.ptr = ft_strdup(command[i]);
			free(cmd->command[i]);
			cmd->command[i] = (char *)utils.ptr;
		}
	}
}
