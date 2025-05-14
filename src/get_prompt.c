/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 05:35:28 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/14 13:31:38 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((cold)) void	get_host(t_prompt *prompt, char **envp, int env_len)
{
	int		i;

	i = -1;
	prompt->host = extract_str_from_strs(envp, \
		"SESSION_MANAGER=local/", ':', env_len);
	if (!prompt->host)
		return ;
	while (prompt->host[++i])
	{
		if (prompt->host[i] == '.')
		{
			prompt->host[i] = '\0';
			break ;
		}
	}
}

__attribute__((hot)) static void	get_prompt(t_prompt *prompt, char **envp, \
	int env_len)
{
	int		lhome;
	int		lpwd;
	char	*tmp;

	prompt->home = get_env(envp, "HOME=", env_len);
	prompt->user = get_env(envp, "USER=", env_len);
	get_host(prompt, envp, env_len);
	prompt->full_pwd = getcwd(NULL, 0);
	lhome = ft_strlen(prompt->home);
	lpwd = ft_strlen(prompt->full_pwd);
	if (prompt->home && prompt->full_pwd && \
		ft_strncmp(prompt->full_pwd, prompt->home, lhome) == 0)
	{
		tmp = ft_substr(prompt->full_pwd, lhome, lpwd - lhome);
		prompt->pwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	else
		prompt->pwd = ft_strdup(prompt->full_pwd);
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
