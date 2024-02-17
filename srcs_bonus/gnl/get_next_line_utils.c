/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:32:05 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/22 15:32:05 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s, char mode)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && (mode != '\n' || s[i] != '\n'))
		i++;
	return (i);
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*res;

	len = gnl_strlen(s, '\n');
	if (gnl_strlen(s, 0) > gnl_strlen(s, '\n'))
		len++;
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	while (len-- > 0)
		res[len] = s[len];
	return (res);
}

void	ft_lstadd_back(t_gnl *data, char *content)
{
	t_gnl_list	*temp;
	t_gnl_list	*new;

	new = malloc(sizeof(*new) * 1);
	if (!new)
	{
		if (content)
			free(content);
		return ;
	}
	new->content = content;
	new->size = gnl_strlen(content, 0);
	data->res_len += new->size;
	new->next = NULL;
	if (!data->lst)
	{
		(data->lst) = new;
		return ;
	}
	temp = data->lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstclear(t_gnl_list **lst, void (*del)(void*))
{
	t_gnl_list	*curr;
	t_gnl_list	*next;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			del(curr->content);
		free(curr);
		curr = next;
	}
}

char	*ft_lstjoin(t_gnl *data)
{
	t_gnl_list	*temp;
	char		*res;

	res = malloc(sizeof(*res) * (data->res_len + 1));
	if (!res)
		return (NULL);
	res[data->res_len] = 0;
	temp = data->lst;
	data->res_len = 0;
	while (temp)
	{
		if (!(temp->content))
		{
			free(res);
			return (NULL);
		}
		ft_memmove(res + data->res_len, temp->content, temp->size);
		data->res_len += temp->size;
		temp = temp->next;
	}
	return (res);
}
