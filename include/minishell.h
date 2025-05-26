/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:33:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/26 14:06:11 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "colors.h"

# define PROMPT_DEFAULT "minishell$ "
# define TMP_HISTORY ".minishell_history"
# define MINIMAL_PATH \
"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef enum e_result
{
	SUCCESS,
	FAIL
}	t_result;
# define RESULT t_result

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
	char		**env;
	int			env_len;
	int			status;
	int			exit_status;
	int			heredoc_quit;
	int			prompt_len_expanded;
	int			prog_status;
	bool		prev_status_is_ctrl_c;
	bool		secret_path;
	pid_t		pid_last;
	pid_t		pid_wait;
	char		*previous_input;
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
int		calc_expanded_length(t_shell *data, const char *input, char **envp, \
	int exit_status);

//REDIRECTION
int		redirection(t_shell *data, char *cmd);

extern int	g_sig;

//EXEC
void	exec(t_shell *data, t_cmd *cmds);
char	*normalize_cd_args(char **env, char *str, int env_len);
void	cd(t_shell *data, char **strs, t_prompt *info);
void	echo(t_shell *data, char **strs);
void	pwd(t_shell *data, char **cmds);
//---------- EXPORT -----------
void	export_var(t_shell *data, char *var);
void	export(t_shell *data, char **var);
bool	is_valid_var_char_env(char *str);
char	*get_var_key(char *var);
void	add_var_to_env(t_shell *data, char *key, char *value);
void	add_value_to_var(char **env, char *key, char *value, int env_len);
void	print_export(t_shell *data, char **strs, int size);
//-----------------------------
void	unset(t_shell *data, char **var);
void	environnement(t_shell *data, char **cmds, char **env, int env_len);
void	exit_minishell(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
int		handle_infile(t_shell *data, t_cmd **cmds);
int		handle_outfile(t_shell *data, t_cmd **cmds);
int		is_builtin(char *cmd);
void	built_in(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
void	builtin_parent_process(t_shell *data, t_cmd *cmd);

// UTILS
char	**find_path(char **envp, int env_len);
char	*find_custom_path(const char *cmd, char **paths);
char	**split_limited(char *str, char c, char *ignored);
void	remove_all_quotes(char **tab);
bool	is_valid_var_char(char c);
char	quote_context_at(const char *str, int pos);
int		append_string(char *out, int o, const char *val);
char	*expand_variables(t_shell *data, char *input);
char	**copy_env(t_shell *data, char **envp);
void	update_var_env(char **env, char *key, char *value, int env_len);
char	*get_env(char **env, char *key, int env_len);
char	**resize_env(t_shell *data, int k);
void	sort_and_print_tab(t_shell *data, char **tab, int size, \
	void (*print)(t_shell *, char **, int));
void	restore_std_fds(int stdin_fd, int stdout_fd);
char	*extract_str_from_strs(char **strs, char *find, char sep, \
	int strs_len);
int		extract_exit_code(int status);
void	wait_exec(t_shell *data);
void	start_and_end(char *cmd, int *s, int *e);
char	*get_filename(char *cmd, int *i);
int		get_fd(t_shell *data, int type, char **file, int fd);
int		create_heredoc_fd(t_shell *data, char **delimiter);
int		find_char(char *str, char c);
void	up_shlvl(t_shell *data, char **env, int env_len);
char	*get_original_var(t_shell *data, char *var);
char	*strip_quotes(const char *s);
void	remove_quotes(char **str, int type);
int		check_limits_value(int *value, int min, int max, int reset);
bool	is_in_heredoc(const char *str, int pos);
int		skip_whitespace(const char *str, int i);
int		is_whitespace(char c);
char	**split_whitespace_limited(char *str, char *ignored);
int		is_print_path(t_shell *data, char *str);

// COMMAND
t_cmd	*init_struct_cmd(t_cmd *prev, char **command, char *line, char **env);
void	get_input_data(t_shell *data);

//FREE
void	free_shell(t_shell *data, int exit_prog);

//SIGNAL
void	sigint_prompt(int sigid);
void	sigint_exec(int sigid);
void	sigint_handler(int sigid);
void	quit_handler(int sigid);
void	handle_sigquit_message(int status, pid_t pid, pid_t last_pid);

#endif
