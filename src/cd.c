/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 15:07:47 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*normalize_cd_args(char **env, char *str, int env_len)
{
	char	*ptr;

	if (!str)
		return (str);
	ptr = NULL;
	if (str[0] == '-')
	{
		if (str[1] == '-' && str[2] == '\0')
			ptr = get_env(env, "HOME=", env_len);
		else if (str[1] == '\0')
		{
			ptr = get_env(env, "OLDPWD=", env_len);
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

static int	setup_cd(t_shell *data, char **strs)
{
	if (strs[1])
	{
		if (strs[2])
			g_sig = 1;
		if (strs[2])
			return (ft_putstr_fd(WHITE"minishell: cd: too many arguments\n"\
				RESET, 2), FAIL);
		strs[1] = normalize_cd_args(data->env, strs[1], data->env_len);
	}
	return (SUCCESS);
}

void	cd(t_shell *data, char **strs, t_prompt *info)
{
	char	*path;
	char	tmp[1024];

	if (setup_cd(data, strs))
		return ;
	if (!strs[1])
		path = ft_strdup(info->home);
	else
		path = ft_substr(strs[1], 0, ft_strlen(strs[1]));
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_sig = 1;
	}
	else
	{
		update_var_env(data->env, "OLDPWD=", info->full_pwd, data->env_len);
		update_var_env(data->env, "PWD=", getcwd(tmp, sizeof(tmp)), \
		data->env_len);
		g_sig = 0;
	}
	free(path);
}
