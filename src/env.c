/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:48:20 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/21 16:39:04 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	environnement(t_shell *data, char **cmds, char **env, int env_len)
{
	int	i;

	i = -1;
	data->exit_status = 0;
	if (!env)
		return ;
	if (cmds[1] && cmds[1][0] == '-')
	{
		ft_putstr_fd(WHITE"minishell: env: -: invalid option\n"RESET, 2);
		data->exit_status = 125;
		return ;
	}
	else if (cmds[1] && cmds[1][0])
	{
		ft_putstr_fd(WHITE"minishell: env: "RESET, 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 127;
		return ;
	}
	while (++i < env_len)
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
