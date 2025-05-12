/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:16:37 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 19:05:57 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**resize_env(t_shell *data, int k)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = -1;
	new_env = (char **)malloc(sizeof(char *) * (data->env_len + 1 + k));
	if (!new_env)
		return (data->env);
	new_env[data->env_len + k] = NULL;
	while (++i < data->env_len)
	{
		if (data->env[i])
			new_env[++j] = data->env[i];
	}
	while (++j < data->env_len + k)
		new_env[j] = NULL;
	free(data->env);
	data->env_len += k;
	data->env = new_env;
	return (data->env);
}

void	unset(t_shell *data, char *var)
{
	int		i;
	int		var_len;
	char	*var_tmp;

	i = -1;
	if (!data->env || !var || !*var)
		return ;
	var_tmp = ft_strjoin(var, "=");
	if (!var_tmp)
		return ;
	var_len = ft_strlen(var_tmp);
	while (++i < data->env_len)
	{
		if (ft_strncmp(data->env[i], var_tmp, var_len) == 0)
		{
			free(data->env[i]);
			data->env[i] = NULL;
			break ;
		}
	}
	free(var_tmp);
	if (i == data->env_len)
		return ;
	data->env = resize_env(data, -1);
}
