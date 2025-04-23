/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:10:11 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/23 16:27:25 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((cold)) TOKEN	get_next_token(char *cmd, t_i32 *i)
{
	while (cmd[++*i])
	{
		//printf("cmd[%d] : %c\n", *i, cmd[*i]);
		//if (cmd[*i] == '<' && cmd[*i + 1] == '<')
		//	return ((t_token){HERDOC, *i, 2});
		//if (cmd[*i] == '<')
		//	return ((t_token){INPUT_REDIREC, *i, 1});
		//if (cmd[*i] == '>' && cmd[*i + 1] == '>')
		//	return ((t_token){APPEND, *i, 2});
		//if (cmd[*i] == '>')
		//	return ((t_token){OUTPUT_REDIREC, *i, 1});
		if (cmd[*i] == '|' && cmd[*i + 1] == '|')
			return ((t_token){OR, *i, 2});
		if (cmd[*i] == '|')
			return ((t_token){PIPE, *i, 1});
		if (cmd[*i] == '&' && cmd[*i + 1] == '&')
			return ((t_token){AND, *i, 2});
	}
	//printf("i : %d\n", *i);
	return ((t_token){NONE, -1, 0});
}
void	create_pipeline(t_pipeline *pipeline)
{
	pipeline->size = 1;
	pipeline->cmd_list = (t_cmd *)ft_calloc(pipeline->size + 1, sizeof(t_cmd));
	if (!pipeline->cmd_list)
		return ;
	pipeline->cmd_list->fd_in = 0;
	pipeline->cmd_list->fd_out = 1;
	pipeline->cmd_list->fd_pipe[0] = -1;
	pipeline->cmd_list->fd_pipe[1] = -1;
	pipeline->cmd_list->command = NULL;
	pipeline->cmd_list->custom_path = NULL;
	pipeline->cmd_list->next = NULL;
	pipeline->cmd_list->prev = NULL;

}

int	main(int argc, char const **argv, char **envp)
{
	t_string	line;
	t_token		token;
	t_i32		start;
	t_i32		end;
	t_prompt	prompt;
	t_pipeline	pipeline;
	char		**cmd;
	int			i;
	int			result_prompt;

	(void)argc;
	(void)argv;
	create_pipeline(&pipeline);
	while (1)
	{
		i = 0;
		end = -1;
		print_prompt(&prompt, envp);
		line.chars = readline("$ ");
		if (!line.chars)
			break ;
		if (*line.chars)
			add_history(line.chars);
		result_prompt = valid_prompt(line.chars);
		if (result_prompt == '\n')
		{
			printf(WHITE"minishell: parse error near `\\n'\n"RESET);
			free(line.chars);
			continue ;
		}
		else if (result_prompt != 0)
		{
			printf(WHITE"minishell: parse error near `%c'\n"RESET, result_prompt);
			free(line.chars);
			continue ;
		}
		cmd = split_limited(line.chars, '|', "\'\"");
		while (cmd && cmd[i])
		{
			start = 0;
			printf(BRED"PIPE %d : %s\n"RESET, i + 1, cmd[i]);
			token = get_next_token(cmd[i], &end);
			while (token.type != NONE)
			{
				if (token.type == AND)
				{
					if (simple_command(cmd[i], start, end, envp))
						break ;
				}
				if (token.type == OR)
				{
					if (!simple_command(cmd[i], start, end, envp))
						break ;
				}
				start = end + token.len;
				token = get_next_token(cmd[i], &end);
			}
			if (token.type == NONE)
			{
				(void)redirection(&pipeline, cmd[i]);
				if (!ft_strncmp(cmd[i], "cd", 2))
					cd(cmd[i], &prompt);
				else if (ft_strncmp(cmd[i], "echo", 4) == 0)
					echo(cmd[i], envp);
				else if (ft_strncmp(cmd[i], "pwd", 3) == 0)
					pwd();
				else if (ft_strncmp(cmd[i], "exit", 4) == 0)
					return (free(line.chars), free_tab(cmd), 0);
				else if (simple_command(cmd[i], start, end, envp))
					continue ;
			}
			end = -1;
			i++;
		}
		free_tab(cmd);
		printf("line: %s\n", line.chars);
		free(line.chars);
	}
	return (0);
}
