/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_limited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:37:14 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:26:44 by tbasak           ###   ########.fr       */
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
	int	i;
	int	j;
	int	count;
	int	ignore;

	i = -1;
	count = 0;
	ignore = 0;
	if (!s)
		return (count);
	while (s[++i])
	{
		j = -1;
		while (ignored[++j])
		{
			if (s[i] == ignored[j] && !ignore)
				ignore = s[i];
			else if (s[i] == ignored[j] && ignore)
				ignore = 0;
		}
		if ((s[i] == sep && s[i + 1] != sep && s[i - 1] != sep && !ignore) \
		|| !s[i + 1])
			count++;
	}
	return (count);
}

static char	*ft_wrdcpy(char **dest, const char *s, int size)
{
	*dest = (char *) ft_calloc(size + 1, sizeof(char));
	if (!dest)
		return (NULL);
	(void) ft_strlcpy(*dest, s, size + 1);
	return (*dest);
}

static int	split(char *str, char c, char *ignored)
{
	int	end;
	int	ignore;

	end = 0;
	ignore = 0;
	while (str[end])
	{
		ignore = is_ignored(str[end], ignored);
		while (ignore)
		{
			end += 1;
			if (str[end] == ignore)
				ignore = 0;
		}
		end += 1;
		if (str[end] == c && str[end + 1] != c && str[end - 1] != c)
			break ;
	}
	return (end);
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
	if (len == 0)
		return (NULL);
	dest = ft_inittab(len);
	end = 0;
	while (word + 1 < len)
	{
		while (str[++start] && str[start] == ' ')
			continue ;
		end = split(&str[start], c, ignored);
		if (ft_wrdcpy(&dest[++word], &str[start], end) == NULL)
			return (NULL);
		start += end;
	}
	return (dest);
}
