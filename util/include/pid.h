/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:38:10 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 08:45:17 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PID_H
# define PID_H

# include "core.h"

typedef t_i32	t_pid;

typedef void	(*t_process_task)(t_pid parent, void *param);

RESULT	spawn_process(t_pid *pid, t_process_task task, void *param);

#endif