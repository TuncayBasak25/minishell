/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 06:53:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/24 10:24:36 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(t_shell *data, char **envp)
{
	int		i;
	int		len;
	char	**env_copy;

	len = 0;
	data->prompt_len_expanded = 1024;
	if (!envp)
		return (NULL);
	while (envp[len])
		len++;
	data->env_len = len;
	env_copy = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		return (NULL);
	env_copy[len] = NULL;
	i = -1;
	while (++i < len)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
			return (free_tab(env_copy));
	}
	return (env_copy);
}

char	*get_env(char **env, char *key, int env_len)
{
	int		i;
	char	*value;

	i = -1;
	if (!env || !key)
		return (NULL);
	while (++i < env_len)
	{
		if (!env[i])
			continue ;
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			value = ft_strdup(&env[i][ft_strlen(key)]);
			return (value);
		}
	}
	return (NULL);
}

char	*get_original_var(t_shell *data, char *var)
{
	int		i;

	i = -1;
	if (!data->env)
		return (NULL);
	while (++i < data->env_len)
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0 && \
		(data->env[i][ft_strlen(var)] == '=' || \
		data->env[i][ft_strlen(var)] == '\0'))
			return (data->env[i]);
	}
	return (NULL);
}
