/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 04:44:25 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 04:51:53 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history(t_shell *data)
{
	int		fd;
	char	*line;

	fd = open(TMP_HISTORY, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(data->previous_input);
		data->previous_input = line;
		line = get_next_line(fd);
	}
	close(fd);
}

void	save_history(t_shell *data)
{
	int	fd;

	if (!data->prompt.user_input || !data->prompt.user_input[0] || \
		data->prompt.user_input[0] == ' ')
		return ;
	if (ft_strcmp(data->prompt.user_input, data->previous_input) == 0)
		return ;
	free(data->previous_input);
	data->previous_input = ft_strdup(data->prompt.user_input);
	fd = open(TMP_HISTORY, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (add_history(data->prompt.user_input));
	add_history(data->prompt.user_input);
	write(fd, data->prompt.user_input, ft_strlen(data->prompt.user_input));
	write(fd, "\n", 1);
	close(fd);
}
