/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:00:15 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/27 06:46:38 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char_env(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	i = -1;
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '+' || \
			str[i] == '=' || str[i] == '_'))
			return (false);
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		else if (str[i] == '+' && str[i + 1] != '=')
			return (false);
		if (str[i] == '=')
			return (true);
	}
	return (true);
}

char	*get_var_key(char *var)
{
	int		i;
	char	*var_key;

	i = 0;
	if (!var || !*var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+')
		i--;
	var_key = ft_substr(var, 0, i);
	if (!var_key)
		return (NULL);
	return (var_key);
}

void	add_var_to_env(t_shell *data, char *key, char *value)
{
	int		i;
	int		len_before_resize;

	i = -1;
	if (!key)
		return ;
	if (!data->env)
		data->env_len = 0;
	len_before_resize = data->env_len;
	resize_env(data, 1);
	if (data->env_len <= len_before_resize)
		return ;
	while (data->env[++i])
		continue ;
	if (value && *value)
	{
		if (*value == '+')
			value++;
		data->env[i] = ft_strjoin(key, value);
	}
	else
		data->env[i] = ft_strdup(key);
}

void	add_value_to_var(char **env, char *key, char *value, int env_len)
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
		if (!ft_strncmp(env[i], key, ft_strlen(key)) && \
		(env[i][ft_strlen(key)] == '=' || env[i][ft_strlen(key)] == '\0'))
		{
			if (env[i][ft_strlen(key)] == '=' && (!*value || \
				(value[0] == '=' && value[1] == '\0')))
				return ;
			if (env[i][ft_strlen(key)] != '=')
				new_var = ft_strjoin(env[i], value);
			else
				new_var = ft_strjoin(env[i], &value[1]);
			free(env[i]);
			env[i] = new_var;
			return ;
		}
	}
}

void	print_export(t_shell *data, char **strs, int size)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < size)
	{
		if (strs[i] && strs[i][0] != '_' && is_print_path(data, strs[i]))
		{
			ft_putstr_fd("declare -x ", 1);
			len = ft_strlen(strs[i]);
			j = -1;
			while (++j < len)
			{
				ft_putchar_fd(strs[i][j], 1);
				if (strs[i][j] == '=')
				{
					printf("\"%s\"\n", &strs[i][j + 1]);
					break ;
				}
				if (!strs[i][j + 1])
					ft_putchar_fd('\n', 1);
			}
		}
	}
}
