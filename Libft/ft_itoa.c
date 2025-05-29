/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:32:34 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 22:48:26 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*dest;

	size = ft_count_digit(n);
	sign = 0;
	dest = (char *) ft_calloc(size + 1, sizeof(char));
	if (!(dest))
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(dest, "-2147483648", 12);
	else if (n < 0)
	{
		n *= -1;
		sign = 1;
		dest[0] = '-';
	}
	while (size - 1 >= sign && n != -2147483648)
	{
		dest[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (dest);
}
