/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:33:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/15 03:46:26 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "colors.h"

# define PROMPT_DEFAULT "minishell$ "
# define HEREDOC_FILE ".heredoc_tmp"

extern int	g_sig;

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
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}	t_operateur;

typedef struct s_utils
{
	int			i;
	int			j;
	int			len;
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
	char		*input;
	char		*out;
	char		**strs;
	char		**tmps;
	const char	*ptr;

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
	int			env_len;
	int			status;
	pid_t		pid_last;
	pid_t		pid_wait;
	t_prompt	prompt;
	t_cmd_group	cmd_group;
}	t_shell;

//TAB
char	**ft_inittab(int size);
void	*free_tab(char **tab);

//PROMPT
void	build_prompt(t_prompt *prompt, char **envp, int env_len);
int		valid_input(t_shell *data);
RESULT	prompt_handling(t_shell *data);

//REDIRECTION
int		redirection(t_cmd_group *pipeline, char *cmd);

//EXEC
void	exec(t_shell *data, t_cmd *cmds);
char	*normalize_cd_args(char **env, char *str, int env_len);
void	cd(t_shell *data, char **strs, t_prompt *info);
void	echo(char **strs);
void	pwd(void);
void	export(t_shell *data, char *var);
void	unset(t_shell *data, char *var);
void	environnement(char **env, int env_len);
void	exit_minishell(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
int		handle_missing_file(t_cmd **cmds);
int		is_builtin(char *cmd);
void	built_in(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
void	builtin_parent_process(t_shell *data, t_cmd *cmd);

// UTILS
char	**find_path(char **envp, int env_len);
char	*find_custom_path(const char *cmd, char **paths);
char	**split_limited(char *str, char c, char *ignored);
char	**split_space_limited(char *str, char c, char *ignored);
void	remove_all_quotes(char **tab);
bool	is_valid_var_char(char c);
bool	is_single_quoted(const char *str, int i);
int		append_string(char *out, int o, const char *val);
char	*expand_variables(char **env, char *raw_input, int env_len);
char	**copy_env(t_shell *data, char **envp);
void	update_var_env(char **env, char *key, char *value, int env_len);
char	*get_env(char **env, char *key, int env_len);
char	**resize_env(t_shell *data, int k);
void	sort_and_print_tab(char **tab, int size);
void	restore_std_fds(int stdin_fd, int stdout_fd);
char	*extract_str_from_strs(char **strs, char *find, char sep, \
	int strs_len);
int		extract_exit_code(int status);
void	wait_exec(t_shell *data);

// COMMAND
t_cmd	*init_struct_cmd(t_cmd *prev, char **command, char *line, char **env);
void	get_input_data(t_shell *data);

//FREE
void	free_shell(t_shell *data, int exit_prog);

#endif
