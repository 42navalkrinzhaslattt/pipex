/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:56:01 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/26 15:56:01 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect(int input_fd, int output_fd, t_data *data)
{
	if (dup2(input_fd, 0) == -1)
		error_exit("dup2", data);
	if (dup2(output_fd, 1) == -1)
		error_exit("dup2", data);
}

int	find_cmd(t_data *data, int n)
{
	char	*temp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		temp = ft_strjoin(data->paths[i], data->cmd[n].name);
		if (!temp)
			error_exit("malloc", NULL);
		if (!access(temp, X_OK))
		{
			data->cmd[n].path = temp;
			return (1);
		}
		free(temp);
	}
	data->cmd[n].path = NULL;
	return (0);
}

void	parse_cmd(char *cmd, t_data *data, int n)
{
	int	i;

	i = 0;
	while (cmd[i] != ' ' && cmd[i] != 0)
		i++;
	data->cmd[n].name = ft_calloc(i + 2, sizeof(*cmd));
	if (!data->cmd[n].name)
		error_exit("malloc", NULL);
	data->cmd[n].name[0] = '/';
	ft_strlcpy(data->cmd[n].name + 1, cmd, i + 1);
	data->cmd[n].argv = ft_split(cmd, ' ');
	if (!data->cmd[n].argv)
		error_exit("malloc", NULL);
	if (!find_cmd(data, n))
	{
		error_exit(cmd, NULL);
		exit(0);
	}
}

void	close_pipes(t_data *data, int n)
{
	int	i;

	if (n == 0)
		close(data->pipefd[0]);
	else if (n == data->nb_cmd - 1)
		close(data->pipefd[1]);
	else
	{
		i = -1;
		while (++i < ((data->nb_cmd - 1) * 2)
			&& i != n * 2 - 2 && i != n * 2 + 1)
			close(data->pipefd[i]);
	}
}

void	child(t_data *data, char *cmd, int n, char **ep)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork", data);
	if (pid == 0)
	{
		if (n == 0)
			redirect(data->infile, data->pipefd[1], data);
		else if (n == data->nb_cmd - 1)
			redirect(data->pipefd[data->nb_cmd * 2 - 4], data->outfile, data);
		else
			redirect(data->pipefd[n * 2 - 2], data->pipefd[n * 2 + 1], data);
		close_pipes(data, n);
		parse_cmd(cmd, data, n);
		execve(data->cmd[n].path, data->cmd[n].argv, ep);
		error_exit("execve", data);
	}
	else
		waitpid(pid, &data->status, 0);
}
