/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 06:12:50 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/16 13:15:02 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_pid_exit(t_shell *data, char *out, char next, int o)
{
	char	*val;

	if (next == '$')
		val = ft_itoa(getpid());
	else
		val = ft_itoa(data->exit_status);
	if (!val)
		return (o);
	o = append_string(out, o, val);
	free(val);
	return (o);
}

static int	handle_dollar(t_utils *utils, char *input, size_t *i, int o)
{
	char	*var;
	char	*val;

	i[0]++;
	if (input[i[0]] == '$' || input[i[0]] == '?')
		return (handle_pid_exit(utils->data, utils->out, input[i[0]++], o));
	if (!is_valid_var_char(input[i[0]]))
	{
		utils->out[o++] = '$';
		return (o);
	}
	i[1] = i[0];
	while (is_valid_var_char(input[i[0]]))
		i[0]++;
	utils->tmp = ft_substr(input, i[1], i[0] - i[1]);
	if (!utils->tmp)
		return (o);
	var = ft_strjoin(utils->tmp, "=");
	free(utils->tmp);
	val = get_env(utils->strs, var, utils->len);
	free(var);
	if (val)
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
	utils->out[o++] = utils->input[(*i)++];
	return (o);
}

char	*expand_variables(t_shell *data, char *raw_input, int env_len)
{
	t_utils	utils;
	size_t	i[2];
	int		o;

	i[0] = 0;
	o = 0;
	utils.input = raw_input;
	utils.out = malloc(ft_strlen(raw_input) + 2000);
	utils.strs = data->env;
	utils.len = env_len;
	utils.data = data;
	if (!utils.out)
		return (raw_input);
	while (raw_input[i[0]])
	{
		if (raw_input[i[0]] == '$' && !is_single_quoted(raw_input, i[0]))
			o = handle_dollar(&utils, raw_input, i, o);
		else if (raw_input[i[0]] == '~')
			o = handle_tilde(&utils, i, o, is_single_quoted(raw_input, i[0]));
		else
			utils.out[o++] = raw_input[i[0]++];
	}
	utils.out[o] = '\0';
	free(raw_input);
	return (utils.out);
}
