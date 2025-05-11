/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:34:54 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/11 18:42:18 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}
