/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/26 11:51:40 by rel-hass         ###   ########.fr       */
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
	if (data->heredoc_quit)
		return (FAIL);
	return (SUCCESS);
}

void	incomplete_env_start(t_shell *data, const char *prog_name)
{
	char	pwd[1024];
	char	*tmp;
	char	*var_pwd;
	char	*var_underscore;

	if (!data->env)
		return ;
	if (*data->env)
	{
		var_underscore = get_original_var(data, "_=");
		if (!var_underscore)
			export_var(data, "_=");
		return (up_shlvl(data, data->env, data->env_len));
	}
	getcwd(pwd, sizeof(pwd));
	var_pwd = ft_strjoin("PWD=", pwd);
	export_var(data, var_pwd);
	export_var(data, "LS_COLORS=");
	export_var(data, "LESSCLOSE=/usr/bin/lesspipe \%s \%s");
	export_var(data, "LESSOPEN=| /usr/bin/lesspipe \%s");
	up_shlvl(data, data->env, data->env_len);
	tmp = ft_strjoin(pwd, prog_name);
	var_underscore = ft_strjoin("_=", tmp);
	export_var(data, var_underscore);
	export_var(data, "OLDPWD");
	free(tmp);
	free(var_pwd);
	free(var_underscore);
}

int	g_sig = 0;

static void	load_history(t_shell *data)
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

void	secret_path(t_shell *data)
{
	if (get_original_var(data, "PATH"))
	{
		data->secret_path = false;
		return ;
	}
	export_var(data, MINIMAL_PATH);
	data->secret_path = true;
}

int	main(int argc, char const **argv, char **envp)
{
	t_shell		data;

	(void)argc;
	(void)argv;
	data = (t_shell){0};
	data.env = copy_env(&data, envp);
	incomplete_env_start(&data, argv[0]);
	secret_path(&data);
	signal(SIGQUIT, SIG_IGN);
	load_history(&data);
	while (1)
	{
		if (!read_and_parse_input(&data))
			exec(&data, data.cmd_group.cmd_list);
		free_shell(&data, 0);
	}
	return (0);
}
