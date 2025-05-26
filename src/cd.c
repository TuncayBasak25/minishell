/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/26 11:52:53 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ptr)
			{
				ft_putstr_fd(ptr, 1);
				ft_putstr_fd("\n", 1);
			}
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
		{
			data->exit_status = 1;
			return (ft_putstr_fd(WHITE"minishell: cd: too many arguments\n"\
				RESET, 2), FAIL);
		}
		strs[1] = normalize_cd_args(data->env, strs[1], data->env_len);
	}
	return (SUCCESS);
}

void	print_error_cd(char *path)
{
	struct stat	buf;

	if ((access(path, F_OK) == -1))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode) == 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Not a directory\n", 2);
		}
		else if (access(path, X_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Permission denied\n"RESET, 2);
		}
	}
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
	if (!path || chdir(path) == -1)
	{
		print_error_cd(path);
		data->exit_status = 1;
	}
	else
	{
		export_var(data, "OLDPWD=");
		update_var_env(data->env, "OLDPWD", info->full_pwd, data->env_len);
		update_var_env(data->env, "PWD", getcwd(tmp, sizeof(tmp)), \
		data->env_len);
		data->exit_status = 0;
	}
	free(path);
}
