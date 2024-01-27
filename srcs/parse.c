/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:25 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/09 17:13:25 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../includes/pipex.h"

void	assign_data(t_data *data, char **av, char **ep, int ac)
{
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->infile == -1 || data->outfile == -1) // remove infile error
		error_exit("open", data);
	data->cmd = ft_calloc(data->nb_cmd, sizeof(t_cmd));
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	data->pipefd = ft_calloc((data->nb_cmd - 1) * 2, sizeof(int));
	if (!data->paths || !data->pipefd)
		error_exit("malloc", data);
	while (--ac - 4 >= 0)
		if (pipe(data->pipefd + 2 * ac - 8) == -1)
			error_exit("pipe", data);
}

void	init_data(t_data *data, char **av, char **ep, int ac)
{
	data->cmd = NULL;
	data->paths = NULL;
	data->nb_cmd = ac - 3;
	data->pipefd = NULL;
	data->outfile = -1;
	data->infile = -1;
	assign_data(data, av, ep, ac);
}
