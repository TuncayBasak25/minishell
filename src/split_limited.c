/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_limited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:37:14 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/04 08:09:40 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ignored(char c, char *ignored)
{
	int	i;

	i = 0;
	while (ignored[i])
	{
		if (c == ignored[i])
			return (ignored[i]);
		i++;
	}
	return (0);
}

static int	counts_word(char *s, char sep, char *ignored)
{
	int		in_word;
	t_utils	u;

	u.i = 0;
	u.count = 0;
	u.ignore = 0;
	in_word = 0;
	while (s && s[u.i])
	{
		if (is_ignored(s[u.i], ignored) && !u.ignore)
			u.ignore = s[u.i];
		else if (s[u.i] == u.ignore)
			u.ignore = 0;
		if (!u.ignore && s[u.i] != sep && !in_word)
		{
			in_word = 1;
			u.count++;
		}
		else if (!u.ignore && s[u.i] == sep)
			in_word = 0;
		u.i++;
	}
	if (u.ignore)
		u.count++;
	return (u.count);
}

static char	*ft_wrdcpy(char **dest, const char *s, int size)
{
	if (!dest)
		return (NULL);
	*dest = (char *) ft_calloc(size + 1, sizeof(char));
	if (!*dest)
		return (NULL);
	(void) ft_strlcpy(*dest, s, size + 1);
	return (*dest);
}

static int	split(char *str, char sep, char *ignored)
{
	int	i;
	int	ignore;

	i = 0;
	ignore = 0;
	while (str[i])
	{
		if (is_ignored(str[i], ignored) && !ignore)
			ignore = str[i];
		else if (str[i] == ignore)
			ignore = 0;
		if (!ignore && str[i] == sep)
			break ;
		i++;
	}
	return (i);
}

char	**split_limited(char *str, char c, char *ignored)
{
	int		start;
	int		end;
	int		word;
	int		len;
	char	**dest;

	dest = NULL;
	start = -1;
	word = -1;
	len = counts_word(str, c, ignored);
	dest = ft_inittab(len);
	if (!dest)
		return (NULL);
	end = 0;
	while (word + 1 < len)
	{
		while (str[++start] && str[start] == ' ')
			continue ;
		end = split(&str[start], c, ignored);
		if (ft_wrdcpy(&dest[++word], &str[start], end) == NULL)
			return (free_tab(dest));
		start += end;
	}
	return (dest);
}
