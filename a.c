/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:21:07 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/17 13:17:08 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

void handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	close(0);
}

int	main(int ac, char *av[])
{
	int	save = dup(0);

	signal(SIGINT, handler);
	readline("HEY");
	dup2(save, 0);
	close(save);
	printf("OUTPUT: %s\n", readline("Hey"));
}

