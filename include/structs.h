/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 04:36:05 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/30 20:28:29 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_utils
{
	int				i;
	int				j;
	size_t			*k;
	int				o;
	int				len;
	int				start;
	int				end;
	int				quote;
	int				repeat;
	int				result_tmp;
	int				result;
	int				ignore;
	int				fd;
	bool			sq;
	bool			dq;
	char			operator;
	char			*str;
	char			*path;
	char			*tmp;
	char			*input;
	char			*output;
	char			*out;
	char			**strs;
	char			**tmps;
	const char		*ptr;
	struct s_shell	*data;

}	t_utils;

typedef struct s_prompt
{
	char		*home;
	char		*user;
	char		*host;
	char		*pwd;
	char		*full_pwd;
	char		*prompt;
	char		*user_input;
}	t_prompt;

typedef struct s_cmd
{
	int				id;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	bool			heredoc;
	char			*line_cmd;
	char			**command;
	char			*custom_path;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmd_group
{
	int			count;
	t_cmd		*cmd_list;
	char		**path;
}	t_cmd_group;

typedef struct s_shell
{
	bool		test_mode;
	char		**env;
	int			env_len;
	int			status;
	int			exit_status;
	int			heredoc_quit;
	int			prompt_len_expanded;
	int			prog_status;
	int			nb_line;
	int			nb_line_heredoc;
	bool		prev_status_is_ctrl_c;
	bool		prev_status_is_ctrl_d;
	bool		secret_path;
	pid_t		pid_last;
	pid_t		pid_wait;
	char		*previous_input;
	t_prompt	prompt;
	t_cmd_group	cmd_group;
}	t_shell;

#endif
