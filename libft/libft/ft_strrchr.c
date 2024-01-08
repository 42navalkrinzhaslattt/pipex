/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:34:27 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/13 19:51:17 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
			res = (char *)s;
		s++;
	}
	if ((char)c == 0)
		res = (char *)s;
	return (res);
}
