/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:34:43 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/22 22:34:44 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*
#include <stdio.h>

int main(void)
{
	t_list	*lst;
	t_list	*lnew;
	char	content1[100] = "1er élément";
	char	content[100];
	char	*content_copy;

	lst = ft_lstnew(content1);
	if (!(lst))
		return (1);
	printf("Nouvelle élément à ajouter au début de la liste : ");
	fgets(content, sizeof(content), stdin);
	//viderBuffer();
	content_copy = (char *) ft_calloc(ft_strlen(content) + 1, sizeof(char));
	if (!(content_copy))
		return (1);
	(void) ft_strlcpy(content_copy, content, ft_strlen(content));
	lnew = ft_lstnew(content_copy);
	if (!(lnew))
	{
		free(content_copy);
		return (1);
	}
	ft_lstadd_front(&lst, lnew);
	printf("\nLst->content: %s\n", (char *) lst->content);
	printf("Lst->next : %p\n", lst->next);
	printf("Lst->next->content : %s\n", (char *) lst->next->content);
	free(lst->content);
	free(lst);
	return (0);
}
*/
