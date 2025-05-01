/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_limited.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:23:46 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 09:26:22 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int	count;
	int	ignore;
	int	in_word;

	i = 0;
	count = 0;
	ignore = 0;
	in_word = 0;
	while (s[i])
	{
		if (is_ignored(s[i], ignored) && !ignore)
			ignore = s[i];
		else if (s[i] == ignore)
			ignore = 0;
		if (!ignore && s[i] != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (!ignore && s[i] == sep)
			in_word = 0;
		i++;
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

char	**split_space_limited(char *str, char c, char *ignored)
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
