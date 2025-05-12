/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 05:35:28 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 02:26:05 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((cold)) void	get_host(t_prompt *prompt, char **envp, int env_len)
{
	int		i;
	char	**host;

	i = -1;
	host = find_path_info(envp, "SESSION_MANAGER=local/", ':', env_len);
	if (!host)
	{
		prompt->host = NULL;
		return ;
	}
	while (host[0][++i])
	{
		if (host[0][i] == '.')
		{
			host[0][i] = '\0';
			break ;
		}
	}
	prompt->host = ft_strdup(*host);
	host = free_tab(host);
}

__attribute__((hot)) static void	get_prompt(t_prompt *prompt, char **envp, \
	int env_len)
{
	int		lhome;
	int		lpwd;
	char	pwd[1024];
	char	*tmp;

	prompt->home = get_env(envp, "HOME=", env_len);
	prompt->user = get_env(envp, "USER=", env_len);
	get_host(prompt, envp, env_len);
	getcwd(pwd, sizeof(pwd));
	prompt->full_pwd = ft_strdup(pwd);
	lhome = ft_strlen(prompt->home);
	lpwd = ft_strlen(pwd);
	if (prompt->home && ft_strncmp(pwd, prompt->home, lhome) == 0)
	{
		tmp = ft_substr(pwd, lhome, lpwd - lhome);
		prompt->pwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	else
		prompt->pwd = ft_strdup(pwd);
}

void	build_prompt(t_prompt *prompt, char **envp, int env_len)
{
	char	*tmp;
	char	*temp_prompt;

	get_prompt(prompt, envp, env_len);
	temp_prompt = ft_strjoin(BGREEN, prompt->user);
	tmp = ft_strjoin(temp_prompt, "@");
	free(temp_prompt);
	temp_prompt = ft_strjoin(tmp, prompt->host);
	free(tmp);
	tmp = ft_strjoin(temp_prompt, RESET);
	free(temp_prompt);
	temp_prompt = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(temp_prompt, BBLUE);
	free(temp_prompt);
	temp_prompt = ft_strjoin(tmp, prompt->pwd);
	free(tmp);
	tmp = ft_strjoin(temp_prompt, RESET);
	free(temp_prompt);
	prompt->prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt->prompt)
		prompt->prompt = ft_strdup("minishell$ ");
}
