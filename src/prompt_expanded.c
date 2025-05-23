/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expanded.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:04:05 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/23 20:11:38 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_length(char *start, int *i)
{
	int	len;

	len = 0;
	if (start[*i] == '?')
	{
		(*i)++;
		return (1);
	}
	while (start[*i] && ((start[*i] >= 'A' && start[*i] <= 'Z') || \
	(start[*i] >= 'a' && start[*i] <= 'z') || \
	(start[*i] >= '0' && start[*i] <= '9') || start[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	return (len);
}

static int	get_expanded_len(char *var_name, char **envp)
{
	int		i;
	size_t	name_len;
	int		var_len;

	i = 0;
	var_len = 0;
	while (envp[i])
	{
		name_len = 0;
		while (envp[i][name_len] && envp[i][name_len] != '=')
			name_len++;
		if (name_len == ft_strlen(var_name) && \
		ft_strncmp(envp[i], var_name, name_len) == 0)
		{
			var_len = ft_strlen(&envp[i][name_len + 1]);
			break ;
		}
		i++;
	}
	return (var_len);
}

static int	exit_status_len(int status)
{
	int	len;

	len = 0;
	if (status == 0)
		return (1);
	while (status)
	{
		status /= 10;
		len++;
	}
	return (len);
}

static void	expanded_lenght(t_utils *u, const char *input, \
	char **envp, int exit_status)
{
	u->i++;
	u->start = u->i;
	if (input[u->i] == '?')
	{
		u->len += exit_status_len(exit_status);
		u->i++;
	}
	else
	{
		get_var_length((char *)input, &u->i);
		u->str = ft_strndup(input + u->start, u->i - u->start);
		if (u->str)
		{
			u->j = get_expanded_len(u->str, envp);
			u->len += u->j;
			free(u->str);
		}
	}
}

int	calc_expanded_length(const char *input, char **envp, int exit_status)
{
	t_utils	u;

	u.i = 0;
	u.len = 0;
	while (input[u.i])
	{
		if (input[u.i] == '$')
			expanded_lenght(&u, input, envp, exit_status);
		else
		{
			u.len++;
			u.i++;
		}
	}
	return (u.len);
}
