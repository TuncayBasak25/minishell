/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:33:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/29 03:44:57 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "colors.h"
# include "structs.h"

# define PROMPT_DEFAULT "minishell$ "
# define TMP_HISTORY ".minishell_history"
# define MINIMAL_PATH \
"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define HEREDOC_WARNING \
"minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n"
# define SUCCESS 0
# define FAIL 1

extern int	g_sig;

typedef enum e_operateur
{
	NONE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}	t_operateur;

// ---------------------------------- HISTORY ----------------------------------
void	load_history(t_shell *data);
void	save_history(t_shell *data);
// -----------------------------------------------------------------------------

// ----------------------------- ARRAY MANAGEMENT ------------------------------
char	**ft_inittab(int size);
void	*free_tab(char **tab);
char	*extract_str_from_strs(char **strs, char *find, char sep, \
	int strs_len);
// -----------------------------------------------------------------------------

// ------------------------------ PROMPT HANDLING ------------------------------
void	build_prompt(t_prompt *prompt, char **envp, int env_len);
int		valid_input(t_shell *data);
int		prompt_handling(t_shell *data);
int		calc_expanded_length(t_shell *data, const char *input, char **envp, \
	int exit_status);
// -----------------------------------------------------------------------------

// ---------------------------------- PARSING ----------------------------------
t_cmd	*init_struct_command(t_shell *data, t_cmd *prev, char *cmd_line, int i);
void	get_input_data(t_shell *data);
char	**find_path(char **envp, int env_len);
char	*find_custom_path(const char *cmd, char **paths);
char	**split_limited(char *str, char c, char *ignored);
char	**split_whitespace_limited(char *str, char *ignored);
void	remove_all_quotes(char **tab);
bool	is_valid_var_char(char c);
char	quote_context_at(const char *str, int pos);
int		append_string(char *out, int o, const char *val);
char	*expand_variables(t_shell *data, char *input);
char	*normalize_cd_args(char **env, char *str, int env_len);
// -----------------------------------------------------------------------------

// -------------------------- ENVIRONMENT MANAGEMENT ---------------------------
bool	is_valid_var_char_env(char *str);
char	*get_var_key(char *var);
void	add_var_to_env(t_shell *data, char *key, char *value);
void	add_value_to_var(char **env, char *key, char *value, int env_len);
void	print_export(t_shell *data, char **strs, int size);
void	export_var(t_shell *data, char *var);
char	**copy_env(t_shell *data, char **envp);
void	update_var_env(char **env, char *key, char *value, int env_len);
char	*get_env(char **env, char *key, int env_len);
char	**resize_env(t_shell *data, int k);
void	sort_and_print_tab(t_shell *data, char **tab, int size, \
	void (*print)(t_shell *, char **, int));
char	*get_original_var(t_shell *data, char *var);
void	up_shlvl(t_shell *data, char **env, int env_len);
void	secret_path(t_shell *data);
void	incomplete_env_start(t_shell *data, const char *prog_name);
// -----------------------------------------------------------------------------

// -------------------------------- REDIRECTION --------------------------------
int		redirection(t_shell *data, char *cmd);
int		handle_infile(t_shell *data, t_cmd **cmds);
int		handle_outfile(t_shell *data, t_cmd **cmds);
int		check_redirection(char *cmd, int *i);
void	start_and_end(char *cmd, int *s, int *e);
char	*get_filename(char *cmd, int *i);
void	fake_heredoc(t_shell *data, char *input);
int		get_fd(t_shell *data, int type, char **file, int fd);
int		create_heredoc_fd(t_shell *data, char **delimiter);
// -----------------------------------------------------------------------------

// --------------------------------- BUILTINS ----------------------------------
int		is_builtin(char *cmd);
void	built_in(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
void	echo(t_shell *data, char **strs);
void	cd(t_shell *data, char **strs, t_prompt *info);
void	pwd(t_shell *data, char **cmds);
void	export(t_shell *data, char **var);
void	unset(t_shell *data, char **var);
void	environnement(t_shell *data, char **cmds, char **env, int env_len);
void	exit_minishell(t_shell *data, t_cmd *cmds, int fd_in, int fd_out);
// -----------------------------------------------------------------------------

// --------------------------------- EXECUTION ---------------------------------
void	exec(t_shell *data, t_cmd *cmds);
void	builtin_parent_process(t_shell *data, t_cmd *cmd);
void	print_error_exec(t_shell *data, t_cmd *cmd);
void	restore_std_fds(int stdin_fd, int stdout_fd);
void	wait_exec(t_shell *data);
int		extract_exit_code(int status);
// -----------------------------------------------------------------------------

// ----------------------------------- UTILS -----------------------------------
int		find_char(char *str, char c);
char	*strip_quotes(const char *s);
void	remove_quotes(char **str, int type);
int		check_limits_value(int *value, int min, int max, int reset);
bool	is_in_heredoc(const char *str, int pos);
int		skip_whitespace(const char *str, int i);
int		is_whitespace(char c);
int		is_ws(char c);
int		is_print_path(t_shell *data, char *str);
// -----------------------------------------------------------------------------

// ---------------------------- CONTROL CHARACTERS -----------------------------
void	sigint_prompt(int sigid);
void	sigint_exec(int sigid);
void	sigint_handler(int sigid);
void	quit_handler(int sigid);
void	handle_sigquit_message(int status, pid_t pid, pid_t last_pid);
// -----------------------------------------------------------------------------

// ----------------------------- SHELL MANAGEMENT -----------------------------
void	free_shell(t_shell *data, int exit_prog);
void	exit_shell(t_shell *data);
// -----------------------------------------------------------------------------

#endif
