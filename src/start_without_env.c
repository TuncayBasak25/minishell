/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_without_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:37:49 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 12:44:41 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_minimal_env(t_shell *data, const char *prog_name)
{
	char	pwd[1024];
	char	*tmp;
	char	*var_pwd;
	char	*var_underscore;

	if (!data->env)
		return ;
	getcwd(pwd, sizeof(pwd));
	var_pwd = ft_strjoin("PWD=", pwd);
	export_var(data, var_pwd);
	export_var(data, "LS_COLORS=");
	export_var(data, "LESSCLOSE=/usr/bin/lesspipe \%s \%s");
	export_var(data, "LESSOPEN=| /usr/bin/lesspipe \%s");
	up_shlvl(data, data->env, data->env_len);
	tmp = ft_strjoin(pwd, prog_name);
	var_underscore = ft_strjoin("_=", tmp);
	export_var(data, var_underscore);
	export_var(data, "OLDPWD");
	free(tmp);
	free(var_pwd);
	free(var_underscore);
}

void	incomplete_env_start(t_shell *data, const char *prog_name)
{
	char	*var_underscore;

	if (!data->env)
		return ;
	if (*data->env)
	{
		var_underscore = get_original_var(data, "_=");
		if (!var_underscore)
			export_var(data, "_=");
		return (up_shlvl(data, data->env, data->env_len));
	}
	export_minimal_env(data, prog_name);
}

void	secret_path(t_shell *data)
{
	if (get_original_var(data, "PATH"))
	{
		data->secret_path = false;
		return ;
	}
	export_var(data, MINIMAL_PATH);
	data->secret_path = true;
}
