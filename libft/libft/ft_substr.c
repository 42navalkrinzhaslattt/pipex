/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:39:14 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/15 14:39:14 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	res_len;

	res_len = len;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < res_len)
		res_len = ft_strlen(s + start);
	res = malloc(sizeof(*res) * (res_len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, res_len + 1);
	return (res);
}
