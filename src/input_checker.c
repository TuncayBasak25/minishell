/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 07:14:54 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/11 20:41:07 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_quote_input(char *prompt, int *i)
{
	int	quote;

	if (prompt[*i] == '\"' || prompt[*i] == '\'')
	{
		quote = prompt[*i];
		while (prompt[++*i] && prompt[*i] != quote)
			continue ;
		if (prompt[*i] == '\0')
			return (quote);
	}
	return (0);
}

static int	check_struct_input(char *p, int *i, char *op, int *repeat)
{
	if (p[*i] == '<' || p[*i] == '>' || p[*i] == '|')
	{
		if (!*op)
			*op = p[*i];
		if (*repeat == 1 && p[*i - 1] == ' ' && (p[*i] == '>' || p[*i] == '<'))
			return (p[*i]);
		if ((*op == p[*i] && *repeat < 2 && (*op == '<' || *op == '>')) || \
		(*op == p[*i] && *repeat < 1 && *op == '|'))
			*repeat += 1;
		else if (*op == '|' && (p[*i] == '<' || p[*i] == '>'))
		{
			*op = p[*i];
			*repeat = 1;
		}
		else
			return (p[*i]);
	}
	else if (p[*i] && p[*i] != ' ')
	{
		if (p[*i] == '&')
			return (p[*i]);
		*repeat = 0;
		*op = 0;
	}
	return (0);
}

static int	check_start_input(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i] && prompt[i] == ' ')
		continue ;
	if (prompt[i] == '&' || prompt[i] == '|')
		return (prompt[i]);
	return (0);
}

static int	input_checker(char *prompt)
{
	t_utils	utils;

	utils.i = -1;
	utils.operator = 0;
	utils.repeat = 0;
	utils.result = check_start_input(prompt);
	if (utils.result)
		return (utils.result);
	while (prompt[++utils.i])
	{
		while (prompt[utils.i] == ' ')
			utils.i++;
		if (prompt[utils.i] == '\0')
			break ;
		utils.result = check_struct_input(prompt, &utils.i, \
			&utils.operator, &utils.repeat);
		if (utils.result)
			return (utils.result);
		utils.quote = check_quote_input(prompt, &utils.i);
		if (utils.quote)
			return (utils.quote);
	}
	if (utils.repeat)
		return ('\n');
	return (0);
}

int	valid_input(t_shell *data)
{
	int	result_prompt;

	result_prompt = input_checker(data->prompt.user_input);
	if (result_prompt == '\n')
	{
		free(data->prompt.user_input);
		data->prompt.user_input = NULL;
		return (printf(WHITE"minishell: parse error near `\\n'\n"RESET));
	}
	else if (result_prompt != 0)
	{
		free(data->prompt.user_input);
		data->prompt.user_input = NULL;
		return (printf(WHITE"minishell: parse error near `%c'\n"RESET, \
			result_prompt));
	}
	return (0);
}
