/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:20:57 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/27 21:20:57 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb > 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	res = malloc((intmax_t)nmemb * (intmax_t)size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, nmemb * size);
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if (size == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dst_len + 1)
		return (size + src_len);
	i = 0;
	while (i + dst_len < size - 1 && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = 0;
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc(sizeof(*s1) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	ft_strlcat(res, s2, s1_len + s2_len + 1);
	return (res);
}
