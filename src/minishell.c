/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:32 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/07 13:33:42 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "readline/readline.h"
#include "readline/history.h"
#include <printf.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "terminal.h"


void	remove_from_history(t_cstr input)
{
	t_i32		i;
    HIST_ENTRY	**hist;
	HIST_ENTRY	*entry;

	hist = history_list();
    if (!hist)
		return ;
	i = -1;
    while (++i < history_length)
	{
        if (strcmp(hist[i]->line, input) == 0) {
            entry = remove_history(i);
			if (entry)
			{
				free(entry->data);
				free(entry->line);
				free(entry);
			}
            break;
        }
    }
}

void	add_unique_history(t_cstr input)
{
	remove_from_history(input);
	add_history(input);
	free(input);
}

t_bool	g_sigint = FALSE;

void	sigint_handler_readline(t_i32 sigid)
{
	(void)sigid;
	write(1, "\n", 1);  // Print newline
	rl_on_new_line();               // Move to new prompt line
	rl_replace_line("", 0);        // Clear the current input
	rl_redisplay(); 
}

void	sigint_handler_normal(t_i32 sigid)
{
	(void)sigid;
	g_sigint = TRUE;
}

t_i32	main(void)
{
	while (TRUE)
	{
		signal(SIGINT, sigint_handler_readline);
		term_restore();
		t_cstr	input = readline("$");
		term_enable_raw_mode();
		signal(SIGINT, sigint_handler_normal);
		if (input == 0)
			continue ;
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		printf("%s\n", input);
		add_unique_history(input);
		sleep(3);//Waitpid
	}
	rl_clear_history();
}
