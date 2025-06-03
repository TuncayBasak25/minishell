/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:53:58 by tbasak            #+#    #+#             */
/*   Updated: 2025/06/02 21:10:48 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	spawn_minishell()
{
	char	*av[2];

	if (fork())
		return ;
	av[0] = "./minishell";
	av[1] = NULL;
	execv("./minishell", av);
	printf("Execv minishell failed!\n");
}

int	main()
{
	spawn_minishell();
	while (1)
	{
		write(0, "cd src\n", 7);
		sleep(1);
	}
	return (0);
}
