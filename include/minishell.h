/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:33:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 09:55:30 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "colors.h"

# define CHAR_MARKER 0x1F

/**
 * @brief Tokens utilisés pour identifier les opérateurs de redirection et de
 * séparation de commandes.
 * 
 * Chaque token est associé à un caractère ou une séquence de caractères 
 * spécifique.
 */
typedef enum e_operateur
{
	NONE,
	INPUT_REDIREC,
	OUTPUT_REDIREC,
	HERDOC,
	APPEND,
	PIPE,
	AND,
	OR,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR,
	AMPERSAND,
	BACKSLASH
}	t_operateur;

typedef struct s_utils
{
	int			i;
	int			j;
	int			start;
	int			end;
	int			quote;
	int			repeat;
	int			result;
	int			ignore;
	bool		sq;
	bool		dq;
	char		operator;
	char		*str;
	char		*path;
	char		*tmp;
	char		**strs;
	char		**tmps;
	const char	*ptr;

}	t_utils;

typedef struct s_token
{
	t_operateur	type;
	t_i32		index;
	t_u32		len;
}	t_token;

typedef struct s_prompt
{
	char		*home;
	char		*user;
	char		*host;
	char		*pwd;
	char		*prompt;
	t_string	user_input;
}	t_prompt;

typedef struct s_cmd
{
	int				id;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
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
	char		**env;
	t_token		token;
	t_prompt	prompt;
	t_cmd_group	cmd_group;
}	t_shell;

//INIT
void	init_struct_shell(t_shell *data);

//TAB
char	**ft_inittab(int size);
void	*free_tab(char **tab);

//PROMPT
void	get_prompt(t_prompt *prompt, char **envp);
void	build_prompt(t_prompt *prompt, char **envp);
void	valid_input(t_shell *data);
RESULT	prompt_handling(t_shell *data);

//REDIRECTION
int		redirection(t_cmd_group *pipeline, char *cmd);

//EXEC
void	exec(t_shell *data);
void	cd(char **str, t_prompt *info);
void	echo(char **str, char **envp);
void	pwd(void);

// UTILS
char	**find_path_info(char **envp, char *info, char sep);
char	**find_path(char **envp);
char	*find_custom_path(const char *cmd, char **paths);
void	error(char *str);
char	**split_limited(char *str, char c, char *ignored);
char	**split_space_limited(char *str, char c, char *ignored);

// COMMAND
t_cmd	*init_struct_cmd(t_cmd *prev, char **command, char *line, char **env);
void	get_input_data(t_shell *data);

#endif
