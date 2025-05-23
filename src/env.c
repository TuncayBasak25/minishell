/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:48:20 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/23 07:09:21 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_var_env(char **env, char *key, char *value, int env_len)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!env || !key || !value)
		return ;
	while (++i < env_len)
	{
		if (!env[i])
			continue ;
		if (!ft_strncmp(env[i], key, ft_strlen(key)) && \
		(env[i][ft_strlen(key)] == '=' || \
		env[i][ft_strlen(key)] == '\0'))
		{
			if (env[i][ft_strlen(key)] == '=' && !*value)
				return ;
			if (value[0] != '=')
				tmp = ft_strjoin(key, "=");
			else
				tmp = ft_strdup(key);
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			return (free(tmp));
		}
	}
}

static void	print_env(char **env, int env_len)
{
	int	i;
	int	j;

	i = -1;
	if (!env)
		return ;
	while (++i < env_len)
	{
		j = -1;
		while (env[i][++j] && env[i][j] != '=')
			continue ;
		if (env[i] && env[i][j] == '=')
			printf("%s\n", env[i]);
	}
}

int	print_error_env(t_shell *data, char **cmds)
{
	if (cmds[1] && cmds[1][0] == '-' && cmds[1][1] != '-' && cmds[1][1])
	{
		ft_putstr_fd("env: invalid option -- '", 2);
		ft_putchar_fd(cmds[1][1], 2);
		ft_putstr_fd("'\n", 2);
		data->exit_status = 125;
		return (1);
	}
	else if (cmds[1] && cmds[1][0] != '-')
	{
		ft_putstr_fd("env: «", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd("»: No such file or directory\n", 2);
		data->exit_status = 127;
		return (1);
	}
	else if (cmds[1] && cmds[1][0] == '-' && cmds[1][1] == '-' && cmds[1][2])
	{
		ft_putstr_fd("env: option « ", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(" » not recognized\n", 2);
		data->exit_status = 125;
		return (1);
	}
	return (0);
}

void	environnement(t_shell *data, char **cmds, char **env, int env_len)
{
	data->exit_status = 0;
	if (!env)
		return ;
	if (print_error_env(data, cmds))
		return ;
	else if (!cmds[1] || (cmds[1][0] == '-' && cmds[1][1] == '-' && \
		!cmds[1][2]))
		print_env(env, env_len);
}
