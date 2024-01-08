/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:55:24 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/14 20:55:24 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_nb_len(int nbr)
{
	int		res;
	long	nb;

	if (nbr == 0)
		return (1);
	nb = nbr;
	res = 0;
	if (nbr < 0)
	{
		res++;
		nb = -nb;
	}
	while (nb > 0)
	{
		res++;
		nb /= 10;
	}
	return (res);
}

char	*ft_itoa(int nbr)
{
	int		len;
	long	nb;
	char	*res;

	nb = nbr;
	len = ft_get_nb_len(nb);
	if (nbr < 0)
		nb = -nb;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	res[len] = 0;
	while (--len >= 0)
	{
		res[len] = nb % 10 + 48;
		nb /= 10;
	}
	if (nbr < 0)
		res[0] = '-';
	return (res);
}
