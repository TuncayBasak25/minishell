/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:42:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/03/30 11:44:18 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((cold)) TOKEN	get_next_token_echo(char *cmd, t_u32 *i)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '\'')
			return ((t_token){SIMPLE_QUOTE, *i, 1});
		if (cmd[*i] == '\"')
			return ((t_token){DOUBLE_QUOTE, *i, 1});
		if (cmd[*i] == '$')
			return ((t_token){DOLLAR, *i, 1});
		if (cmd[*i] == '&')
			return ((t_token){AMPERSAND, *i, 1});
		if (cmd[*i] == '\\')
			return ((t_token){BACKSLASH, *i, 1});
		*i += 1;
	}
	return ((t_token){NONE, *i, 0});
}

void	echo(char *str, char **envp)
{
	t_u32	i;
	t_i32	j;
	char	**env;
	char	*arg;
	t_token	token;

	i = 4;
	env = NULL;
	arg = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	if (str[i] == '\0')
		return ((void) printf("\n"));
	token = get_next_token_echo(str, &i);
	while (str[j])
	{
		printf("j : %d\n", j);
		if (token.type == NONE)
		{
			printf("%d\n", token.len - j);
			write(1, &str[j], j);
			j += token.len;
			printf("%d\n", token.len);
		}
		else if (token.type == SIMPLE_QUOTE)
		{
			while (str[++j] && str[j] != '\'')
				printf("%c", str[j]);
		}
		else if (token.type == DOUBLE_QUOTE)
		{
			while (str[++j] && str[j] != '\"')
				printf("%c", str[j]);
		}
		else if (token.type == DOLLAR)
		{
			while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] \
				!= '\"' && str[i] != '$' && str[i] != '&' && str[i] != '\\')
				continue ;
			arg = ft_substr(str, j, i - 1);
			env = find_path_info(envp, arg, '\0');
			if (env)
				printf("%s", *env);
		}
		//token = get_next_token_echo(str, &i);
		while (str[j] && str[j] == ' ')
			j++;
		j++;
	}
	printf("\n");
	if (env)
		free_tab(env);
	if (arg)
		free(arg);
}
