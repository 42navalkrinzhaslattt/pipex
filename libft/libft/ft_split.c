/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:38:38 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/15 14:38:38 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_str(char const *str, char sep)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			res++;
		i++;
	}
	return (res);
}

static int	count_strlen(char const *str, char sep, int n)
{
	int	i;
	int	counter;
	int	res;

	i = 0;
	res = 0;
	counter = -1;
	while (str[i])
	{
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			counter++;
		if (n == counter && !is_sep(str[i], sep))
			res++;
		i++;
	}
	return (res);
}

static char	*save_str(char const *str, char sep, int n)
{
	int		i;
	int		j;
	int		counter;
	char	*res;

	i = 0;
	j = 0;
	counter = -1;
	res = (char *)malloc((count_strlen(str, sep, n) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			counter++;
		if (n == counter && !is_sep(str[i], sep))
			res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = count_str(s, c);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[size] = 0;
	i = 0;
	while (i < size)
	{
		res[i] = save_str(s, c, i);
		if (!res[i])
		{
			while (i-- > 0)
				free(res[i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}
