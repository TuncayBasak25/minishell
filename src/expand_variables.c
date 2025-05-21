/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 06:12:50 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 20:03:40 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_heredoc(const char *str, int pos)
{
	int		i;
	bool	in_heredoc;

	i = 0;
	in_heredoc = false;
	while (i < pos)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			in_heredoc = true;
			i += 2;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
				i++;
			continue ;
		}
		in_heredoc = false;
		i++;
	}
	return (in_heredoc);
}

static int	handle_exit(t_shell *data, char *out, char c, int o)
{
	char	*val;

	(void)c;
	val = ft_itoa(data->exit_status);
	if (!val)
		return (o);
	o = append_string(out, o, val);
	free(val);
	return (o);
}

static int	expand_variable(t_utils *utils, char *input, size_t *i, int o)
{
	char	*key;
	char	*val;
	char	*search;

	i[0]++;
	if (input[i[0]] == '?')
		return (handle_exit(utils->data, utils->out, input[i[0]++], o));
	if (!is_valid_var_char(input[i[0]]))
		return (utils->out[o++] = '$', o);
	i[1] = i[0];
	while (is_valid_var_char(input[i[0]]))
		i[0]++;
	key = ft_substr(input, i[1], i[0] - i[1]);
	search = ft_strjoin(key, "=");
	free(key);
	val = get_env(utils->strs, search, utils->len);
	free(search);
	o = append_string(utils->out, o, val);
	free(val);
	return (o);
}

static int	handle_tilde(t_utils *utils, size_t *i, int o, bool sq)
{
	char	*home;

	if (*i == 0 || utils->input[*i - 1] == ' ')
	{
		home = get_env(utils->strs, "HOME=", utils->len);
		if (!sq && home)
		{
			o = append_string(utils->out, o, home);
			free(home);
			(*i)++;
			return (o);
		}
	}
	return (utils->out[o++] = utils->input[(*i)++], o);
}

char	*expand_variables(t_shell *data, char *input, int env_len)
{
	t_utils	u;

	u.input = input;
	u.o = 0;
	u.k = (size_t []){0, 0};
	if (!input || !*input)
		return (input);
	u.out = malloc(ft_strlen(input) * (ft_strlen(input) + 100));
	if (!u.out)
		return (input);
	u.strs = data->env;
	u.len = env_len;
	u.data = data;
	while (input[u.k[0]])
	{
		if (input[u.k[0]] == '$'
			&& !is_single_quoted(input, u.k[0])
			&& !is_in_heredoc(input, u.k[0]))
			u.o = expand_variable(&u, input, u.k, u.o);
		else if (input[u.k[0]] == '~')
			u.o = handle_tilde(&u, u.k, u.o, is_single_quoted(input, u.k[0]));
		else
			u.out[u.o++] = input[u.k[0]++];
	}
	u.out[u.o] = '\0';
	free(input);
	return (u.out);
}
