/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:44:27 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/09 14:44:27 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../includes/pipex.h"

void	free_cmd(t_cmd cmd)
{
	int	i;

	if (cmd.name)
		free(cmd.name);
	if (cmd.path)
		free(cmd.path);
	if (cmd.argv)
	{
		i = -1;
		while (cmd.argv[++i])
			free(cmd.argv[i]);
		free(cmd.argv);
	}
}

void	error_exit(char *str, t_data *data)
{
	int	i;

	if (ft_strncmp(str, "OK", 3))
		perror(str);
	i = -1;
	if (data->cmd != 0)
		while (++i < data->nb_cmd)
			free_cmd(data->cmd[i]);
	if (data->cmd)
		free(data->cmd);
	if (data->paths)
	{
		i = -1;
		while (data->paths[++i])
			free(data->paths[i]);
		free(data->paths);
	}
	i = -1;
	while (++i < (data->nb_cmd - 1) * 2)
		close(data->pipefd[i]);
	if (data->pipefd)
		free(data->pipefd);
	exit(EXIT_FAILURE);
}
