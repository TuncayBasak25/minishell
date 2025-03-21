/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:32 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 11:21:26 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "string.h"
#include "fd.h"
#include <stdio.h>

#define BACK_SPACE '\x7F'
#define UP "\033[A"
#define DOWN "\033[B"
#define RIGHT "\033[C"
#define LEFT "\033[D"

RESULT	push_input_until_endline(t_string *input)
{
	char	c;
	t_u32	ignore;

	c = 0;
	while (TRUE)
	{
		if (fd_read_to_buffer(FD_STDIN, &c, 1, &ignore) == FAIL)
			return (fail(FNAME));
		if (c == BACK_SPACE)
		{
			fd_write_cstring(FD_STDOUT, LEFT " " LEFT);//Move left, write space and move left again to erase one char
			input->len--;//We remove the last char
			continue ;//We keep reading
		}
		fd_write_char(FD_STDOUT, c);
		if (c == '\n')
			return (SUCCESS);
		string_push_char(input, c);
	}
	return (SUCCESS);
}

int	main()
{
	t_string	input;
	t_i32		exit_status;

	if (term_enable_raw_mode() == FAIL)
		return (fail("Unable to setup terminal in raw mode!"));
	string_init(&input);
	exit_status = 0;
	while (TRUE)
	{
		if (push_input_until_endline(&input) == FAIL)
		{
			exit_status = 1;
			break ;
		}
		fd_write_cstring(FD_STDOUT, "New command! [");
		fd_write_string(FD_STDOUT, &input);
		printf("] len[%u]\n\n", input.len);
		input.len = 0;
	}
	string_destroy(&input);
	if (term_restore() == FAIL)
		return (fail("Unable to restore terminal to original state!"));
	return (exit_status);
}
