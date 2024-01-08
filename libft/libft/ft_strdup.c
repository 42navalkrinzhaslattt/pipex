/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:27:32 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/14 20:27:32 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*res;

	len = ft_strlen(s);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, s, len + 1);
	return (res);
}
