/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_all_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 07:40:57 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 13:13:15 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(const char *s)
{
	char	*dst;
	int		i;
	int		j;
	char	q;

	dst = malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q)
				dst[j++] = s[i++];
			if (s[i] == q)
				i++;
		}
		else
			dst[j++] = s[i++];
	}
	dst[j] = '\0';
	return (dst);
}

void	remove_quotes(char **str, int type)
{
	char	*new;

	if (!str || !*str || type == HEREDOC)
		return ;
	new = strip_quotes(*str);
	free(*str);
	*str = new;
}

void	remove_all_quotes(char **tab)
{
	char	*new;

	if (!tab || !*tab)
		return ;
	while (*tab)
	{
		new = strip_quotes(*tab);
		free(*tab);
		*tab = new;
		tab++;
	}
}
