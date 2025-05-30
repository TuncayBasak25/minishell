/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:04:23 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/30 15:13:16 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_expand_char(char c)
{
	return ((ft_isalnum(c) || c == '_' || c == '$') && c != '\'' && c != '\"');
}

char	quote_context_at(const char *str, int pos)
{
	bool	sq;
	bool	dq;
	int		j;

	sq = false;
	dq = false;
	j = -1;
	while (++j < pos && str[j])
	{
		if (str[j] == '\'' && !dq)
			sq = !sq;
		else if (str[j] == '"' && !sq)
			dq = !dq;
	}
	if (sq)
		return ('\'');
	else if (dq)
		return ('"');
	return (0);
}

int	append_string(char *dst, int o, const char *val)
{
	int	j;

	j = 0;
	while (val && val[j])
		dst[o++] = val[j++];
	return (o);
}

bool	is_in_heredoc(const char *str, int pos)
{
	int		i;
	bool	in_heredoc;

	i = 0;
	in_heredoc = false;
	while (i < pos)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (quote_context_at(str, i) == '\"')
				return (in_heredoc);
			in_heredoc = true;
			i += 2;
			while (str[i] && is_whitespace(str[i]))
				i++;
			while (str[i] && !is_whitespace(str[i]))
				i++;
			continue ;
		}
		in_heredoc = false;
		i++;
	}
	return (in_heredoc);
}
