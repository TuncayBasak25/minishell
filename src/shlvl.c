/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:39:15 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/21 16:47:40 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limits_value(int *value, int min, int max, int reset)
{
	if (*value < min || *value > max)
	{
		*value = reset;
		return (1);
	}
	return (0);
}

void	up_shlvl(t_shell *data, char **env, int env_len)
{
	int		i;
	int		new_value;
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
			new_value = ft_atoi(shlvl) + 1;
			if (check_limits_value(&new_value, 1, 999, 1))
				printf(WHITE"minishell: warning: shell level (%d) too high, \
resetting to 1\n"RESET, new_value);
			new_shlvl = ft_itoa(new_value);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", new_shlvl);
			return (free(new_shlvl), free(shlvl));
		}
	}
	if (i == env_len)
		export(data, "SHLVL=1");
}
