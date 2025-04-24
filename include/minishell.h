/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:33:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/24 12:30:29 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "colors.h"

/**
 * @brief Tokens utilisés pour identifier les opérateurs de redirection et de
 * séparation de commandes.
 * 
 * Chaque token est associé à un caractère ou une séquence de caractères spécifique.
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

typedef struct s_token
{
	t_operateur	type;
	t_i32		index;
	t_u32		len;
}	t_token;
# define TOKEN t_token __attribute__((warn_unused_result))

typedef struct s_prompt
{
	char	*home;
	char	*user;
	char	*host;
	char	*pwd;
	char	*prompt;
}	t_prompt;

typedef struct s_cmd
{
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
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
	t_string	user_input;
	t_token		token;
	t_prompt	prompt;
	t_cmd_group	cmd_group;
}	t_shell;

//TAB
char	**ft_inittab(int size);
void	*free_tab(char **tab);

//PROMPT
void	print_prompt(t_prompt *prompt, char **envp);
void	valid_prompt(t_shell *data);
RESULT	prompt_handling(t_shell *data);

//REDIRECTION
int		redirection(t_cmd_group *pipeline, char *cmd);

//EXEC
RESULT	simple_command(char *cmd, t_i32 start, t_i32 end, char **envp);
void	cd(char *str, t_prompt *info);
void	echo(char *str, char **envp);
void	pwd(void);

// UTILS
char	**find_path_info(char **envp, char *info, char sep);
char	**find_path(char **envp);
char	*find_custom_path(const char *cmd, char **paths);
void	error(char *str);
char	**split_limited(char *str, char c, char *ignored);

#endif
