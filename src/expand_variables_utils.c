/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:04:23 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:12:52 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_single_quoted(const char *str, int i)
{
	bool	sq;
	bool	dq;
	int		j;

	sq = false;
	dq = false;
	j = -1;
	while (++j < i)
	{
		if (str[j] == '\'' && !dq)
			sq = !sq;
		else if (str[j] == '"' && !sq)
			dq = !dq;
	}
	return (sq);
}

int	append_string(char *out, int o, const char *val)
{
	int	i;

	i = 0;
	while (val[i])
		out[o++] = val[i++];
	return (o);
}
