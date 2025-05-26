/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:50:40 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/26 14:32:20 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
