/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:36:30 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/22 22:36:32 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*f_lst;
	void	*content;

	start = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			content = f(lst->content);
			f_lst = ft_lstnew(content);
			if (!(f_lst))
			{
				del(content);
				ft_lstclear(&start, del);
				return (NULL);
			}
			ft_lstadd_back(&start, f_lst);
			lst = lst->next;
		}
	}
	return (start);
}
