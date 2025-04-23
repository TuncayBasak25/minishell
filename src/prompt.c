/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/23 23:02:47 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_prompt_info(t_prompt *info, char **envp)
{
	char	**host;
	char	pwd[1024];
	char	*tmp;
	int		i;

	i = -1;
	info->home = getenv("HOME");
	info->user = getenv("USER");
	host = find_path_info(envp, "SESSION_MANAGER=local/", ':');
	while (host[0][++i])
	{
		if (host[0][i] == '.')
		{
			host[0][i] = '\0';
			break ;
		}
	}
	getcwd(pwd, sizeof(pwd));
	info->host = ft_strdup(*host);
	free_tab(host);
	if (ft_strncmp(pwd, info->home, ft_strlen(info->home)) == 0)
	{
		info->pwd = ft_strdup("~");
		tmp = ft_substr(pwd, ft_strlen(info->home), ft_strlen(pwd) - ft_strlen(info->home));
		info->pwd = ft_strjoin(info->pwd, tmp);
		free(tmp);
	}
	else
		info->pwd = ft_strdup(pwd);
}

void	print_prompt(t_prompt *prompt, char **envp)
{
	get_prompt_info(prompt, envp);
	printf(BGREEN"%s@%s"RESET, prompt->user, prompt->host);
	printf(":");
	printf(BBLUE"%s"RESET, prompt->pwd);
}

int	valid_prompt(char *prompt)
{
	int		i;
	int		repeat;
	char	operator;
	char	quote;

	i = -1;
	operator = 0;
	quote = 0;
	repeat = 0;
	while (prompt[++i])
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\0')
			break ;
		if (prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|' || prompt[i] == '&')
		{
			if (!operator)
				operator = prompt[i];
			if (operator == prompt[i] && repeat < 2)
				repeat++;
			else if ((operator == '|' || operator == '&') && (prompt[i] == '<' || prompt[i] == '>'))
			{
				operator = prompt[i];
				repeat = 1;
			}
			else
				return (prompt[i]);
		}
		else if (prompt[i])
		{
			if (operator == '&' && repeat == 1)
				return (operator);
			repeat = 0;
			operator = 0;
		}
		if (prompt[i] == '\"' || prompt[i] == '\'')
		{
			quote = prompt[i];
			while (prompt[++i] && prompt[i] != quote)
				continue ;
			if (prompt[i] == '\0')
				return (quote);
		}
	}
	if (repeat)
		return ('\n');
	return (0);
}
