/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:21:41 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 20:50:31 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	limit = LLONG_MAX;
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
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_status = 2;
		restore_std_fds(fd_in, fd_out);
		free_shell(data, 1);
		exit(data->exit_status);
	}
}

void	exit_minishell(t_shell *data, t_cmd *cmds, int fd_in, int fd_out)
{
	if (cmds->command[1])
	{
		exit_is_digit_arg(data, cmds, fd_in, fd_out);
		if (cmds->command[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->exit_status = 1;
			return ;
		}
		else
			data->exit_status = (ft_atoi(cmds->command[1]) % 256 + 256) % 256;
		restore_std_fds(fd_in, fd_out);
		free_shell(data, 1);
		exit(data->exit_status);
	}
	restore_std_fds(fd_in, fd_out);
	free_shell(data, 1);
	if (data->prev_status_is_ctrl_c == false)
		data->exit_status = 0;
	exit(data->exit_status);
}
