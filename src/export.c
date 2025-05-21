/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:50:40 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 13:12:14 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_var_char_env(char c)
{
	return (ft_isalpha(c) || c == '_');
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
	if (var[i] == '=')
		i++;
	var_key = ft_substr(var, 0, i);
	if (!var_key)
		return (NULL);
	return (var_key);
}

char	*get_original_var(t_shell *data, char *var)
{
	int		i;

	i = -1;
	if (!data->env)
		return (NULL);
	while (++i < data->env_len)
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0)
			return (data->env[i]);
	}
	return (NULL);
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

void	export(t_shell *data, char *var)
{
	int		var_len;
	char	*var_key;
	char	*var_env;

	if (!var || !*var)
		return (sort_and_print_tab(data, data->env, data->env_len));
	if (is_valid_var_char_env(var[0]) == false)
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
	if (ft_strlen(&var[var_len]) == 0 && var[var_len - 1] != '=')
		return (free(var_key));
	if (var_env)
		update_var_env(data->env, var_key, &var[var_len], data->env_len);
	else
		add_var_to_env(data, var);
	free(var_key);
}
