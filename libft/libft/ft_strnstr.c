/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:53:08 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/14 17:53:08 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	reach;

	if (!big && len == 0)
		return (NULL);
	reach = ft_strlen(little);
	if (!reach && little != 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i + reach <= len)
	{
		if (ft_strncmp(big + i, little, reach) != 0)
			i++;
		else
			return ((char *)big + i);
	}
	return (0);
}
