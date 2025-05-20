/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:34:20 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/22 22:34:21 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *) ft_calloc(1, sizeof(t_list));
	if (!(lst))
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

/*
#include <stdio.h>

void viderBuffer(void)
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int main(void)
{
	t_list	*lst;
	char	content[1000];
	char	*content_copy;

	printf("Contenu de la liste : ");
	fgets(content, sizeof(content), stdin);
	//viderBuffer();
	content_copy = (char *) ft_calloc(ft_strlen(content) + 1, sizeof(char));
	if (!(content_copy))
		return (1);
	(void) ft_strlcpy(content_copy, content, ft_strlen(content));
	lst = ft_lstnew(content_copy);
	if (!(lst))
	{
		free(content_copy);
		return (1);
	}
	printf("\nLst->content : %s\n", (char *) lst->content);
	printf("Lst->next : %p\n", lst->next);
	free(lst->content);
	free(lst);
	return (0);
}
*/
