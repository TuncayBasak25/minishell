/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:15:49 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 10:41:44 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables_in_heredoc(t_shell *data, char *input)
{
	size_t	*i;
	char	*expanded;

	i = (size_t []){0, 0};
	expanded = NULL;
	if (!input || !*input)
		return (input);
	while (input[i[0]])
	{
		if (input[i[0]] == '$')
			expanded = expand_variable(data, input, expanded, i);
		else
			expanded = ft_push_char_to_string(expanded, input[i[0]++]);
	}
	free(input);
	return (expanded);
}
