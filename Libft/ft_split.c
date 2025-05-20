/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:51:28 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/22 21:51:36 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counts_word(char const *s, char c)
{
	int	i;
	int	back;
	int	counts_word;

	i = -1;
	back = 1;
	counts_word = 0;
	while (s[++i])
	{
		if (s[i] != c && back == 1)
		{
			back = 0;
			counts_word++;
		}
		else if (s[i] == c && back == 0)
			back = 1;
	}
	return (counts_word);
}

static char	*ft_wrdcpy(char **dest, int start, const char *s, int size)
{
	dest[start] = (char *) ft_calloc(size + 1, sizeof(char));
	if (!(dest[start]))
	{
		while (start >= 0)
		{
			free(dest[start]);
			start--;
		}
		free(dest);
		return (NULL);
	}
	(void) ft_strlcpy(dest[start], s, size + 1);
	return (*dest);
}

static char	**ft_inittab(int size)
{
	char	**str;

	str = (char **) ft_calloc(size + 1, sizeof(char *));
	if (!(str))
		return (NULL);
	str[size] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dest;

	i = -1;
	j = -1;
	if (!(s))
		return (NULL);
	dest = ft_inittab(ft_counts_word(s, c));
	while (s[++i] && dest)
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			k = i;
		else if (s[i] == c && i != 0 && s[i - 1] != c)
		{
			if (!(ft_wrdcpy(dest, ++j, &s[k], i - k)))
				return (NULL);
		}
		if (!(s[i + 1]) && i != 0 && s[i] != c \
			&& !ft_wrdcpy(dest, ++j, &s[k], i - k + 1))
			return (NULL);
	}
	return (dest);
}
