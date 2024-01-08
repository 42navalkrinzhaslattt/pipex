/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:57:44 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/14 21:57:44 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin_trim;
	size_t	end_trim;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	begin_trim = 0;
	end_trim = 0;
	i = 0;
	while (is_set(s1[i++], set))
		begin_trim++;
	if (i == ft_strlen(s1) + 1)
		return (ft_strdup(""));
	i = ft_strlen(s1) - 1;
	while (is_set(s1[i--], set))
		end_trim++;
	res = malloc(sizeof(*s1) * (ft_strlen(s1) - begin_trim - end_trim + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + begin_trim, ft_strlen(s1) - begin_trim - end_trim + 1);
	return (res);
}
