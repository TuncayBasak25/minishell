/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:04:23 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 13:12:03 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_single_quoted(const char *str, int pos)
{
	bool	sq;
	bool	dq;
	int		j;

	sq = false;
	dq = false;
	j = -1;
	while (++j < pos)
	{
		if (str[j] == '\'' && !dq)
			sq = !sq;
		else if (str[j] == '"' && !sq)
			dq = !dq;
	}
	return (sq);
}

int	append_string(char *dst, int o, const char *val)
{
	int	j;

	j = 0;
	while (val && val[j])
		dst[o++] = val[j++];
	return (o);
}
