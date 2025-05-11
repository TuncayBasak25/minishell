/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/11 21:05:13 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*normalize_cd_args(char **env, char *str)
{
	char	*ptr;

	if (!str)
		return (str);
	ptr = NULL;
	if (str[0] == '-')
	{
		if (str[1] == '-' && str[2] == '\0')
			ptr = get_env(env, "HOME=");
		else if (str[1] == '\0')
		{
			ptr = get_env(env, "OLDPWD=");
			ft_putstr_fd(ptr, 1);
			ft_putstr_fd("\n", 1);
		}
		if (!ptr)
			return (str);
		free(str);
		return (ptr);
	}
	return (str);
}

void	cd(t_shell *data, char **str, t_prompt *info)
{
	char	*path;

	if (!str[1])
		path = ft_strdup(info->home);
	else
		path = ft_substr(str[1], 0, ft_strlen(str[1]));
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_sig = 1;
	}
	else
	{
		update_var_env(data->env, "OLDPWD=", info->full_pwd);
		g_sig = 0;
	}
	free(path);
}
