/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:15:49 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/30 12:25:00 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables_in_heredoc(t_shell *data, char *input)
{
	t_utils	u;

	u.input = input;
	u.o = 0;
	u.k = (size_t []){0, 0};
	if (!input || !*input)
		return (input);
	u.out = malloc(data->prompt_len_expanded + 1);
	if (!u.out)
		return (input);
	u.strs = data->env;
	u.len = data->env_len;
	u.data = data;
	while (input[u.k[0]])
	{
		if (input[u.k[0]] == '$')
			u.o = expand_variable(&u, input, u.k, u.o);
		else if (input[u.k[0]] == '~')
			u.o = handle_tilde(&u, u.k, u.o);
		else
			u.out[u.o++] = input[u.k[0]++];
	}
	u.out[u.o] = '\0';
	free(input);
	return (u.out);
}
