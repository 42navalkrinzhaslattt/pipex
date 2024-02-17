/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:26:48 by nam-vu            #+#    #+#             */
/*   Updated: 2023/11/22 15:26:48 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	if (c == 0 && n == (size_t)(BUFFER_SIZE + 1))
		return (NULL);
	return (s);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	ssize_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < (ssize_t)n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	return (dest);
}

char	*gnl_flush(t_gnl *data)
{
	char	*res;

	res = gnl_strdup(data->buf);
	if (!res)
		return (NULL);
	ft_memmove(data->buf, data->buf + gnl_strlen(data->buf, '\n'),
		gnl_strlen(data->buf, 0) - gnl_strlen(data->buf, '\n'));
	gnl_memset(data->buf + gnl_strlen(data->buf, 0)
		- gnl_strlen(res, '\n'), 0, gnl_strlen(res, '\n'));
	if (data->buf[0] == '\n')
	{
		ft_memmove(data->buf, data->buf + 1, gnl_strlen(data->buf, 0) - 1);
		gnl_memset(data->buf + gnl_strlen(data->buf, 0) - 1, 0, 1);
	}
	data->flush_flag = 0;
	if (gnl_strlen(data->buf, 0) > gnl_strlen(data->buf, '\n'))
		data->flush_flag = 1;
	return (res);
}

char	*parser(int fd, t_gnl *data)
{
	ssize_t			nbytes;

	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, data->buf, BUFFER_SIZE);
		if (gnl_strlen(data->buf, '\n') < gnl_strlen(data->buf, 0)
			|| nbytes < BUFFER_SIZE)
		{
			if (nbytes < 0 || (nbytes == 0 && !(data->res_len)))
			{
				gnl_memset(data->buf, 0, BUFFER_SIZE + 1);
				data->flush_flag = 0;
				return (NULL);
			}
			ft_lstadd_back(data, gnl_flush(data));
			return (ft_lstjoin(data));
		}
		ft_lstadd_back(data, gnl_strdup(data->buf));
		gnl_memset(data->buf, 0, BUFFER_SIZE + 1);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_gnl	data;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, data.buf, 0) < 0)
		return (gnl_memset(data.buf, 0, BUFFER_SIZE + 1));
	data.res_len = 0;
	data.lst = NULL;
	if (data.flush_flag == 1)
	{
		ft_lstadd_back(&data, gnl_flush(&data));
		res = ft_lstjoin(&data);
		ft_lstclear(&(data.lst), &free);
		if (res && res[0] == 0)
		{
			free(res);
			return (NULL);
		}
		return (res);
	}
	ft_lstadd_back(&data, gnl_flush(&data));
	res = parser(fd, &data);
	ft_lstclear(&(data.lst), &free);
	return (res);
}
