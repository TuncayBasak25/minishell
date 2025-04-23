/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:44:53 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 08:46:04 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pid.h"
#include <unistd.h>
#include <stdlib.h>

RESULT	spawn_process(t_pid *pid, t_process_task task, void *param)
{
	t_pid	parent;

	parent = getpid();
	*pid = fork();
	if (*pid == -1)
		return (fail(FNAME));
	if (*pid == 0)
	{
		task(parent, param);
		exit(EXIT_SUCCESS);
	}
	return (SUCCESS);
}
