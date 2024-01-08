/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:54:31 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/16 22:54:31 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*temp;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	temp = lst;
	res = NULL;
	while (temp)
	{
		new = ft_lstnew(f(temp->content));
		if (!new)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		temp = temp->next;
	}
	return (res);
}
