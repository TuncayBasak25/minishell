/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:50:40 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 22:25:45 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_var_export(char **strs, int *i, int *j)
{
	ft_putchar_fd(strs[*i][*j], 1);
	if (strs[*i][*j] == '=' && strs[*i][*j + 1] != '\"')
		return (printf("\"%s\"\n", &strs[*i][*j + 1]));
	else if (strs[*i][*j] == '=' && strs[*i][*j + 1] == '\"')
	{
		ft_putstr_fd("\"\\\"", 1);
		++*j;
		while (strs[*i][++*j] && strs[*i][*j] != '\"')
		{
			if (strs[*i][*j] == '$')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(strs[*i][*j], 1);
		}
		ft_putchar_fd('\\', 1);
		ft_putstr_fd("\"\"\n", 1);
		return (1);
	}
	if (!strs[*i][*j + 1])
		return (ft_putchar_fd('\n', 1));
	return (0);
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
				if (print_var_export(strs, &i, &j))
					break ;
			}
		}
	}
}

void	export_var(t_shell *data, char *var)
{
	int		var_len;
	char	*var_key;
	char	*var_env;

	var_key = get_var_key(var);
	if (!var_key)
		return ;
	var_len = ft_strlen(var_key);
	var_env = get_original_var(data, var_key);
	if (!ft_strncmp(var, "PATH", 4))
		data->secret_path = false;
	if (var_env && var[var_len] == '+' && var[var_len + 1] == '=')
		add_value_to_var(data->env, var_key, &var[var_len + 1], data->env_len);
	else if (var_env && var[var_len])
		update_var_env(data->env, var_key, &var[var_len], data->env_len);
	else if (!var_env)
		add_var_to_env(data, var_key, &var[var_len]);
	free(var_key);
}

void	export(t_shell *data, char **var)
{
	int		i;

	if (!var || !*var)
		return (sort_and_print_tab(data, data->env, data->env_len, \
			print_export));
	i = -1;
	data->exit_status = 0;
	while (var[++i])
	{
		if (is_valid_var_char_env(var[i]) == false)
		{
			data->exit_status = 1;
			ft_putstr_fd("minishell: export: « ", 2);
			ft_putstr_fd(var[i], 2);
			ft_putstr_fd(" »: not a valid identifier\n", 2);
			continue ;
		}
		export_var(data, var[i]);
	}
}
