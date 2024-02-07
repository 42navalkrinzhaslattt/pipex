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

static void	redirect_input(t_data *data, int flag)
{
	int	fd;

	fd = STDIN_FILENO;
	if (flag & FD_FILE_IN)
	{
		fd = open(data->infile, O_RDONLY);
		if (fd < 0)
			ft_error("pipex", data->infile, data, E_OPEN_FAIL);
	}
	else if (flag & FD_PIPE_IN)
		fd = data->pipefd[0];
	else if (flag & FD_PREV_IN)
		fd = data->prev_fd_in;
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_error("pipex", NULL, data, E_DUP2_FAIL);
	if (fd != STDIN_FILENO)
		close(fd);
	if (!(flag & FD_PIPE_IN))
		close(data->pipefd[0]);
	if (!(flag & FD_PREV_IN) && data->prev_fd_in > 0)
		close(data->prev_fd_in);
}

static void	redirect_output(t_data *data, int flag)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (flag & FD_FILE_OUT)
	{
		fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			ft_error("pipex", data->outfile, data, E_OPEN_FAIL);
	}
	else if (flag & FD_PIPE_OUT)
		fd = data->pipefd[1];
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_error("pipex", NULL, data, E_DUP2_FAIL);
	if (fd != STDOUT_FILENO)
		close(fd);
	if (!(flag & FD_PIPE_OUT))
		close(data->pipefd[1]);
}

static int	find_cmd(t_data *data)
{
	int		i;
	int		exist_flag;

	i = -1;
	exist_flag = 0;
	while (data->paths[++i])
	{
		data->cmd.path = ft_strjoin(data->paths[i], data->cmd.file);
		if (!data->cmd.path)
			ft_error("pipex", NULL, data, E_MALLOC_FAIL);
		if (!access(data->cmd.path, F_OK))
			exist_flag = 1;
		if (!access(data->cmd.path, X_OK))
			return (1);
		free(data->cmd.path);
		data->cmd.path = NULL;
	}
	if (exist_flag)
		ft_error("pipex", PATH_PERM_MSG, data, E_PATH_PERM);
	else
		ft_error("pipex", INV_CMD_MSG, data, E_INV_CMD_FAIL);
	return (0);
}

void	create_child(char *cmd, int flag, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork", NULL, data, E_FORK_FAIL);
	if (pid == 0)
	{
		data->cmd.argv = ft_split(cmd, ' ');
		data->cmd.file = ft_strjoin("/", data->cmd.argv[0]);
		if (!data->cmd.argv || !data->cmd.file)
			ft_error("pipex", NULL, data, E_MALLOC_FAIL);
		if (!data->cmd.argv[0])
			ft_error("pipex", EMPTY_CMD_MSG, data, E_EMPTY_CMD);
		redirect_input(data, flag);
		redirect_output(data, flag);
		find_cmd(data);
		execve(data->cmd.path, data->cmd.argv, data->envp);
		ft_error("pipex", NULL, data, E_EXECVE_FAIL);
	}
}
