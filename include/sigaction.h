/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:36:22 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 14:40:16 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGACTION_H
# define SIGACTION_H

# define _POSIX_C_SOURCE 200809L
# define _DEFAULT_SOURCE

# include <signal.h>
# include <unistd.h>
# include "util.h"

typedef void	(*t_sa_handler)(t_i32 sigid, siginfo_t *info, void *context);

RESULT		setup_sigaction(int sig, t_sa_handler handler);

#endif