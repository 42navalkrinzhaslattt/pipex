/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:11:13 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/14 20:11:13 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb > 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	res = malloc((intmax_t)nmemb * (intmax_t)size);
	if (!res)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}
