/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/02 14:06:38 by rel-hass         ###   ########.fr       */
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
	while (is_whitespace(*s))
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
		while (*s && !is_whitespace(*s) && *s != '<' && *s != '>')
			s++;
	}
	return (s);
}

static char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (is_whitespace(*start))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && is_whitespace (*end))
		*end-- = '\0';
	return (ft_strdup(start));
}

static char	*get_command(char *input)
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

t_cmd	*init_struct_command(t_shell *data, t_cmd *prev, char *cmd_line, int id)
{
	t_cmd	*current;

	current = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!current || !cmd_line)
		return (free(current), NULL);
	current->id = id + 1;
	current->fd_out = 1;
	current->line_cmd = get_command(cmd_line);
	current->command = split_whitespace_limited(current->line_cmd, "\'\"");
	remove_all_quotes(current->command);
	if (current->command && find_char(current->command[0], '/'))
		current->custom_path = ft_strdup(current->command[0]);
	else if (current->command)
		current->custom_path = \
		find_custom_path(current->command[0], data->cmd_group.path);
	current->next = NULL;
	current->prev = prev;
	if (current->prev)
		current->prev->next = current;
	else
		data->cmd_group.cmd_list = current;
	if (data->cmd_group.cmd_list->next)
		data->cmd_group.cmd_list = data->cmd_group.cmd_list->next;
	(void) redirection(data, cmd_line);
	return (current);
}

void	get_input_data(t_shell *data)
{
	char	**tab;
	t_utils	u;
	t_cmd	*prev;

	u.i = -1;
	tab = split_limited(data->prompt.user_input, '|', "\'\"");
	if (!tab)
		return ;
	data->cmd_group.path = find_path(data->env, data->env_len);
	prev = NULL;
	while (tab[++u.i])
	{
		u.str = get_command(tab[u.i]);
		tab[u.i] = expand_variables(data, tab[u.i]);
		u.strs = split_whitespace_limited(u.str, "\'\"");
		prev = init_struct_command(data, prev, tab[u.i], u.i);
		if (!prev)
			return (free(u.str), (void) free_tab(u.strs), (void) free_tab(tab));
		regularization(data, prev, u.strs);
		free_tab(u.strs);
		free(u.str);
		if (data->heredoc_quit)
			break ;
	}
	free_tab(tab);
}
