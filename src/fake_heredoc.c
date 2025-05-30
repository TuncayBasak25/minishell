/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:15:14 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/30 12:11:26 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fake_heredoc(t_shell *data, char *input)
{
	int		i;
	int		fd;
	int		redirection;
	char	*delimiter;

	i = -1;
	if (!input)
		return ;
	while (1)
	{
		i++;
		redirection = check_redirection(input, &i);
		if (redirection != HEREDOC && input[i])
			continue ;
		if (!input[i] || !input[i + 1] || \
			input[i + 1] == '<' || input[i + 1] == '>')
			break ;
		delimiter = get_filename(&input[i], &i);
		fd = create_heredoc_fd(data, &delimiter);
		free(delimiter);
		if (g_sig != SIGINT && fd > 2)
			close(fd);
	}
}
