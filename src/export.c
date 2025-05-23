/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:50:40 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/23 07:02:37 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_var_char_env(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (true);
			else if (str[i] == '+' && str[i + 1] != '=')
				return (false);
			if (str[i] == '=')
				return (true);
		}
		return (true);
	}
	return (false);
}

static char	*get_var_key(char *var)
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

static void	add_var_to_env(t_shell *data, char *var)
{
	int		i;

	i = -1;
	if (!var)
		return ;
	if (!data->env)
		data->env_len = 0;
	resize_env(data, 1);
	while (data->env[++i])
		continue ;
	data->env[i] = ft_strdup(var);
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

void	export(t_shell *data, char *var)
{
	int		var_len;
	char	*var_key;
	char	*var_env;

	if (!var || !*var)
		return (sort_and_print_tab(data, data->env, data->env_len));
	if (is_valid_var_char_env(var) == false)
	{
		data->exit_status = 1;
		return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(var, 2), \
		ft_putstr_fd("': not a valid identifier\n", 2));
	}
	data->exit_status = 0;
	var_key = get_var_key(var);
	if (!var_key)
		return ;
	var_len = ft_strlen(var_key);
	var_env = get_original_var(data, var_key);
	if (var_env && var[var_len] == '+' && var[var_len + 1] == '=')
		add_value_to_var(data->env, var_key, &var[var_len + 1], data->env_len);
	else if (var_env && var[var_len])
		update_var_env(data->env, var_key, &var[var_len], data->env_len);
	else if (!var_env)
		add_var_to_env(data, var);
	free(var_key);
}
