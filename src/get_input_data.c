/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 08:58:32 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		q = *s++;
		while (*s && *s != q)
			s++;
		if (*s == q)
			s++;
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

void	remove_first_quote(char **tab)
{
	char	*s;
	char	*pos;
	char	*pos2;
	char	quote;

	while (*tab)
	{
		s = *tab;
		pos = ft_strchr(s, '\'');
		pos2 = ft_strchr(s, '"');
		if (!pos || (pos2 && pos2 < pos))
			pos = pos2;
		if (!pos)
		{
			tab++;
			continue ;
		}
		quote = *pos;
		ft_memmove(pos, pos + 1, ft_strlen(pos));
		pos = ft_strchr(pos, quote);
		if (pos)
			ft_memmove(pos, pos + 1, ft_strlen(pos));
		tab++;
	}
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
	utils.strs = split_limited(data->prompt.user_input.chars, '|', "\'\"");
	prev = NULL;
	if (!utils.strs)
		return ;
	data->cmd_group.path = find_path(data->env);
	while (utils.strs[++utils.i])
	{
		utils.str = get_command(utils.strs[utils.i]);
		if (!utils.str)
			return ((void) free_tab(utils.strs));
		utils.tmps = split_space_limited(utils.str, ' ', "\'\"");
		if (!utils.tmps)
			return ((void) free(utils.str), (void) free_tab(utils.strs));
		remove_first_quote(utils.tmps);
		data->cmd_group.cmd_list = init_struct_cmd(prev, utils.tmps, \
			utils.str, data->cmd_group.path);
		data->cmd_group.cmd_list->id = utils.i + 1;
		(void) redirection(&data->cmd_group, utils.strs[utils.i]);
		prev = data->cmd_group.cmd_list;
	}
	utils.strs = free_tab(utils.strs);
}
