/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:51:28 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 15:15:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**tab_push(char **tab, char *word)
{
	size_t	i;
	size_t	len;
	char	**new_tab;

	len = 0;
	while (tab && tab[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (++i < len)
		new_tab[i] = tab[i];
	new_tab[len] = word;
	new_tab[len + 1] = NULL;
	free(tab);
	return (new_tab);
}

static char	**split_and_push(char **tab, char *expanded)
{
	size_t	i;
	char	**words;

	if (!expanded)
		return (tab);
	words = split_whitespace_limited(expanded, NULL);
	free(expanded);
	if (!words)
		return (tab);
	i = -1;
	while (words[++i])
	{
		tab = tab_push(tab, ft_strdup(words[i]));
		if (!tab)
			return (NULL);
	}
	free_tab(words);
	return (tab);
}

char	**expand_and_split(t_shell *data, char **argv)
{
	size_t	i;
	char	*expanded;
	char	**result;

	if (!argv || !*argv)
		return (NULL);
	i = -1;
	expanded = NULL;
	result = NULL;
	while (argv[++i])
	{
		expanded = expand_variables(data, argv[i]);
		if (!expanded)
			return ((void) free_tab(result), argv);
		result = split_and_push(result, expanded);
		if (!result)
			return (argv);
	}
	free(argv);
	return (result);
}
