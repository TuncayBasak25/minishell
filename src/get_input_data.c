/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/22 18:11:59 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_redir(const char *s)
{
	char	op;
	char	q;

	op = *s++;
	if (*s == op)
		s++;
	while (*s == ' ')
		s++;
	if (*s == '\'' || *s == '"')
	{
		while (*s == '\'' || *s == '"')
		{
			q = *s++;
			while (*s && *s != q)
				s++;
			if (*s == q)
				s++;
		}
	}
	else
	{
		while (*s && *s != ' ' && *s != '<' && *s != '>')
			s++;
	}
	return (s);
}

static char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (*start == ' ')
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && *end == ' ')
		*end-- = '\0';
	return (ft_strdup(start));
}

char	*get_command(char *input)
{
	t_utils	utils;

	utils.ptr = input;
	utils.str = malloc(ft_strlen(input) + 1);
	if (!utils.str)
		return (NULL);
	utils.i = 0;
	utils.sq = false;
	utils.dq = false;
	while (*utils.ptr)
	{
		if (*utils.ptr == '\'' && !utils.dq)
			utils.sq = !utils.sq;
		else if (*utils.ptr == '"' && !utils.sq)
			utils.dq = !utils.dq;
		if (!utils.sq && !utils.dq && (*utils.ptr == '<' || *utils.ptr == '>'))
			utils.ptr = skip_redir(utils.ptr);
		else
			utils.str[utils.i++] = *utils.ptr++;
	}
	utils.str[utils.i] = '\0';
	utils.ptr = trim_spaces(utils.str);
	free(utils.str);
	return ((char *)utils.ptr);
}

void	get_input_data(t_shell *data)
{
	t_utils	utils;
	t_cmd	*prev;

	utils.i = -1;
	utils.strs = split_space_limited(data->prompt.user_input, '|', "\'\"");
	prev = NULL;
	if (!utils.strs)
		return ;
	data->cmd_group.path = find_path(data->env, data->env_len);
	while (utils.strs[++utils.i])
	{
		utils.str = get_command(utils.strs[utils.i]);
		if (!utils.str)
			return ((void) free_tab(utils.strs));
		utils.tmps = split_space_limited(utils.str, ' ', "\'\"");
		remove_all_quotes(utils.tmps);
		data->cmd_group.cmd_list = init_struct_cmd(prev, utils.tmps, \
			utils.str, data->cmd_group.path);
		data->cmd_group.cmd_list->id = utils.i + 1;
		(void) redirection(data, utils.strs[utils.i]);
		if (data->heredoc_quit)
			return ;
		prev = data->cmd_group.cmd_list;
	}
	utils.strs = free_tab(utils.strs);
}
