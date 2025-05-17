/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:48:20 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/17 09:09:39 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	up_shlvl(t_shell *data, char **env, int env_len)
{
	int		i;
	char	*shlvl;
	char	*new_shlvl;

	i = -1;
	if (!env)
		return ;
	while (++i < env_len)
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			shlvl = ft_strdup(&env[i][6]);
			new_shlvl = ft_itoa(ft_atoi(shlvl) + 1);
			free(shlvl);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", new_shlvl);
			free(new_shlvl);
			return ;
		}
	}
	if (i == env_len)
		export(data, "SHLVL=1");
}

char	**copy_env(t_shell *data, char **envp)
{
	int		i;
	int		len;
	char	**env_copy;

	len = 0;
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

void	update_var_env(char **env, char *key, char *value, int env_len)
{
	int		i;
	char	*new_var;

	i = -1;
	if (!env || !key || !value)
		return ;
	while (++i < env_len)
	{
		if (!env[i])
			continue ;
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			new_var = ft_strjoin(key, value);
			env[i] = new_var;
			return ;
		}
	}
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

void	environnement(t_shell *data, char **env, int env_len)
{
	int	i;

	i = -1;
	data->exit_status = 0;
	if (!env)
		return ;
	while (++i < env_len)
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
