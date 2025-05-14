/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:21:41 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/14 23:23:16 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_ll_overflow(const char *str)
{
	int					sign;
	unsigned long long	nb;
	unsigned long long	limit;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	limit = 9223372036854775807ULL;
	if (sign == -1)
		limit += 1;
	while (*str >= '0' && *str <= '9')
	{
		if (nb > (limit - (*str - '0')) / 10)
			return (1);
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (0);
}

static int	nb_is_digit(char *str)
{
	int	i;

	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_is_digit_arg(t_shell *data, t_cmd *cmds, int fd_in, int fd_out)
{
	int			isdigit;
	long long	limit;

	(void) data;
	isdigit = nb_is_digit(cmds->command[1]);
	if (isdigit)
		limit = is_ll_overflow(cmds->command[1]);
	if (!isdigit || limit)
	{
		ft_putstr_fd(WHITE"minishell: exit: ", 2);
		ft_putstr_fd(cmds->command[1], 2);
		ft_putstr_fd(": numeric argument required\n"RESET, 2);
		g_sig = 2;
		restore_std_fds(fd_in, fd_out);
		free_shell(data, 1);
		exit(g_sig);
	}
}

void	exit_minishell(t_shell *data, t_cmd *cmds, int fd_in, int fd_out)
{
	if (cmds->command[1])
	{
		exit_is_digit_arg(data, cmds, fd_in, fd_out);
		if (cmds->command[2])
		{
			ft_putstr_fd(WHITE"minishell: exit: too many arguments\n"RESET, 2);
			g_sig = 1;
			return ;
		}
		else
			g_sig = (ft_atoi(cmds->command[1]) % 256 + 256) % 256;
		restore_std_fds(fd_in, fd_out);
		free_shell(data, 1);
		exit(g_sig);
	}
	restore_std_fds(fd_in, fd_out);
	free_shell(data, 1);
	g_sig = 0;
	exit(g_sig);
}
