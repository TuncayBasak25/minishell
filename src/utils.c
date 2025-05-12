/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 08:26:03 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 02:45:56 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief	Recherche et extrait la variable d'environnement PATH.
 *
 *	Cette fonction parcourt les variables d'environnement fournies dans
 *	`envp`, cherche la variable `PATH` et la divise en un tableau de chaînes
 *	représentant chaque chemin contenu dans `PATH`.
 *
 * @param envp	Tableau des variables d'environnement sous forme de chaînes de 
 * 				caractères. Doit être valide et se terminer par un pointeur NULL.
 * 
 * @return	Un tableau de chaînes (chemins de `PATH` séparés par des `:`) si la 
 * 			variable est trouvée et correctement divisée.
 * 			Retourne `NULL` si `PATH` est introuvable ou si une allocation 
 * 			échoue.
 *
 * @note	Le tableau renvoyé doit être libéré par l'utilisateur avec une 
 * 			fonction appropriée comme `ft_free_tab`.
 * @warning	La fonction suppose que `envp` est un tableau valide terminé par 
 * 			`NULL`.
 */
char	**find_path(char **envp, int env_len)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (++i < env_len)
	{
		if (!envp[i])
			continue ;
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}

/**
 * @brief	Recherche le chemin absolu d'une commande exécutable.
 *
 *	Cette fonction parcourt les chemins contenus dans le tableau `paths` et 
 * 	tente de construire le chemin absolu d'une commande. Elle teste chaque 
 *	chemin en ajoutant le nom de la commande (`cmd`) et en vérifiant si ce 
 *	chemin est valide et accessible via `access`.
 *
 * @param cmd	La commande à rechercher (par exemple, "ls").
 * @param paths	Un tableau de chaînes contenant les chemins extraits de PATH.
 * 
 * @return	Une chaîne contenant le chemin absolu si la commande est trouvée.
 * 			Si la commande n'est pas trouvée, la fonction renvoie une copie de
 * 			`cmd` (qui peut être utilisée pour afficher un message d'erreur).
 *
 * @note	La chaîne renvoyée doit être libérée par l'appelant après usage.
 * 
 * @warning	Si un échec d'allocation mémoire se produit, la fonction retourne 
 * 			immédiatement `NULL`. Il est donc essentiel de valider le pointeur 
 * 			retourné.
 */
char	*find_custom_path(const char *cmd, char **paths)
{
	int		i;
	int		a;
	char	*path;
	char	*part_path;

	i = -1;
	if (paths)
	{
		while (paths[++i])
		{
			part_path = ft_strjoin(paths[i], "/");
			if (!part_path)
				return (NULL);
			path = ft_strjoin(part_path, cmd);
			free(part_path);
			if (!path)
				return (NULL);
			a = access(path, F_OK);
			if (!a)
				return (path);
			free(path);
		}
	}
	path = ft_strdup(cmd);
	return (path);
}

char	**find_path_info(char **envp, char *info, char sep, int env_len)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (++i < env_len)
	{
		if (!envp[i])
			continue ;
		if (!ft_strncmp(envp[i], info, ft_strlen(info)))
		{
			path = ft_split(envp[i] + ft_strlen(info), sep);
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}
