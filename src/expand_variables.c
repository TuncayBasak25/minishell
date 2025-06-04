/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 06:12:50 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 11:01:26 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_expandable_tilde(const char *input, size_t i)
{
	return ((i == 0 && (is_ws(input[i + 1]) || input[i + 1] == '/' || \
	!input[i + 1])) || ((is_ws(input[i + 1]) || input[i + 1] == '/' || \
	!input[i + 1]) && i > 0 && is_ws(input[i - 1])));
}

static char	*handle_dollar_exit(t_shell *data, char *expanded, char c)
{
	char	*val;

	if (c == '$')
		return (ft_push_string_to_string(expanded, EASTEREGG));
	val = ft_itoa(data->exit_status);
	if (!val)
		return (expanded);
	expanded = ft_push_string_to_string(expanded, val);
	free(val);
	return (expanded);
}

char	*expand_variable(t_shell *data, char *input, char *expanded, size_t *i)
{
	char	*key;
	char	*val;
	char	*search;

	i[0]++;
	if (input[i[0]] == '$' || input[i[0]] == '?')
		return (handle_dollar_exit(data, expanded, input[i[0]++]));
	if (!is_valid_var_char(input[i[0]]) && input[i[0]] != '$')
		return (ft_push_char_to_string(expanded, '$'));
	i[1] = i[0];
	while (is_valid_expand_char(input[i[0]]))
	{
		i[0]++;
		if (ft_isdigit(input[i[0] - 1]) && input[i[0] - 2] == '$')
			break ;
	}
	key = ft_substr(input, i[1], i[0] - i[1]);
	search = ft_strjoin(key, "=");
	free(key);
	val = get_env(data->env, search, data->env_len);
	free(search);
	expanded = ft_push_string_to_string(expanded, val);
	free(val);
	return (expanded);
}

static char	*expand_variables_norme(t_shell *data, char *input, \
	char *expanded, size_t *i)
{
	if (input[i[0]] == '$' && quote_context_at(input, i[0]) != '\'' && \
		!is_in_heredoc(input, i[0]) && input[i[0] + 1] != '\'' && \
		input[i[0] + 1] != '\"')
		expanded = expand_variable(data, input, expanded, i);
	else if (input[i[0]] == '~' && !quote_context_at(input, i[0]) && \
		!is_in_heredoc(input, i[0]) && is_expandable_tilde(input, i[0]))
	{
		expanded = ft_push_string_to_string(expanded, data->tilde);
		i[0]++;
	}
	else
	{
		if (input[i[0]] == '$' && !quote_context_at(input, i[0]) && \
		(input[i[0] + 1] == '\'' || input[i[0] + 1] == '\"'))
			i[0]++;
		else
			expanded = ft_push_char_to_string(expanded, input[i[0]++]);
	}
	return (expanded);
}

char	*expand_variables(t_shell *data, char *input)
{
	size_t	*i;
	char	*expanded;

	expanded = NULL;
	i = (size_t []){0, 0};
	if (!input || !*input)
		return (input);
	while (input[i[0]])
		expanded = expand_variables_norme(data, input, expanded, i);
	free(input);
	return (expanded);
}
