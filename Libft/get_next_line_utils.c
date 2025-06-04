/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:42:49 by lsaiti            #+#    #+#             */
/*   Updated: 2025/02/04 21:15:49 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_freestr(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_strjoin_ledion(char *s1, char const *s2, long n)
{
	size_t	total_len;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (ft_freestr(&s1));
	total_len = ft_strlen(s1) + n;
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (ft_freestr(&s1), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < n)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}

void	reset_gnl(t_buffer b[])
{
	int	i;

	i = -1;
	while (++i < 1024)
	{
		*b[i].buffer = 0;
		b[i].buff_pos = 0;
		b[i].bytesread = 0;
		b[i].buff_read = 0;
	}
}
