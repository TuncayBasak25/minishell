/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 13:11:02 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_head(t_shell *data)
{
	if (!data->cmd_group.cmd_list)
		return ;
	while (data->cmd_group.cmd_list->prev)
		data->cmd_group.cmd_list = data->cmd_group.cmd_list->prev;
}

RESULT	read_and_parse_input(t_shell *data)
{
	if (prompt_handling(data))
		return (FAIL);
	get_input_data(data);
	go_to_head(data);
	return (SUCCESS);
}

void	incomplete_env_start(t_shell *data, const char *prog_name)
{
	char	pwd[1024];
	char	*tmp;
	char	*var_pwd;
	char	*var_underscore;

	if (*data->env)
	{
		var_underscore = get_original_var(data, "_=");
		if (!var_underscore)
			export(data, "_=");
		return (up_shlvl(data, data->env, data->env_len));
	}
	getcwd(pwd, sizeof(pwd));
	var_pwd = ft_strjoin("PWD=", pwd);
	export(data, var_pwd);
	export(data, "LS_COLORS=");
	export(data, "LESSCLOSE=/usr/bin/lesspipe \%s \%s");
	export(data, "LESSOPEN=| /usr/bin/lesspipe \%s");
	up_shlvl(data, data->env, data->env_len);
	tmp = ft_strjoin(pwd, prog_name);
	var_underscore = ft_strjoin("_=", tmp);
	export(data, var_underscore);
	free(tmp);
	free(var_pwd);
	free(var_underscore);
}

int	g_sig = 0;

void	load_history(void)
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
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	data = (t_shell){0};
	data.env = copy_env(&data, envp);
	incomplete_env_start(&data, argv[0]);
	signal(SIGQUIT, SIG_IGN);
	load_history();
	while (1)
	{
		if (!read_and_parse_input(&data))
			exec(&data, data.cmd_group.cmd_list);
		free_shell(&data, 0);
	}
	return (0);
}
