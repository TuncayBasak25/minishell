/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:49:16 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/24 13:08:08 by rel-hass         ###   ########.fr       */
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

int	verif_quote_prompt(char *prompt, int *i)
{
	int	quote;

	if (prompt[*i] == '\"' || prompt[*i] == '\'')
	{
		quote = prompt[*i];
		printf("%c\n", prompt[*i]);
		while (prompt[++*i] && prompt[*i] != quote)
			continue ;
		if (prompt[*i] == '\0')
			return (quote);
	}
	return (0);
}

int	verif_struct_prompt(char *prompt, int *i, char *operator, int *repeat)
{
	if (prompt[*i] == '<' || prompt[*i] == '>' || prompt[*i] == '|' || prompt[*i] == '&')
	{
		if (!*operator)
			*operator = prompt[*i];
		if (*operator == prompt[*i] && *repeat < 2)
			*repeat += 1;
		else if ((*operator == '|' || *operator == '&') && (prompt[*i] == '<' || prompt[*i] == '>'))
		{
			*operator = prompt[*i];
			*repeat = 1;
		}
		else
			return (prompt[*i]);
	}
	else if (prompt[*i])
	{
		if (*operator == '&' && *repeat == 1)
			return (*operator);
		*repeat = 0;
		*operator = 0;
	}
	return (0);
}
int	verif_start_prompt(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i] && prompt[i] == ' ')
		continue ;
	if (prompt[i] == '&' || prompt[i] == '|')
		return (prompt[i]);
	return (0);
}

int	verif_prompt(char *prompt)
{
	int		i;
	int		repeat;
	int		quote;
	char	operator;
	int		result;

	i = -1;
	operator = 0;
	repeat = 0;
	result = verif_start_prompt(prompt);
	if (result)
		return (result);
	while (prompt[++i])
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\0')
			break ;
		result = verif_struct_prompt(prompt, &i, &operator, &repeat);
		if (result)
			return (result);
		quote = verif_quote_prompt(prompt, &i);
		if (quote)
			return (quote);
	}
	if (repeat)
		return ('\n');
	return (0);
}

void	valid_prompt(t_shell *data)
{
	int	result_prompt;

	result_prompt = verif_prompt(data->user_input.chars);
	if (result_prompt == '\n')
	{
		printf(WHITE"minishell: parse error near `\\n'\n"RESET);
		free(data->user_input.chars);
		data->user_input.chars = NULL;
	}
	else if (result_prompt != 0)
	{
		printf(WHITE"minishell: parse error near `%c'\n"RESET, result_prompt);
		free(data->user_input.chars);
		data->user_input.chars = NULL;
	}
}

RESULT	prompt_handling(t_shell *data)
{
	print_prompt(&data->prompt, data->env);
	data->user_input.chars = readline("$ ");
	if (!data->user_input.chars)
		return (FAIL);
	if (data->user_input.chars)
		add_history(data->user_input.chars);
	valid_prompt(data);
	return (SUCCESS);
}
