/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:41:17 by nam-vu            #+#    #+#             */
/*   Updated: 2024/02/15 23:41:17 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (data->heredoc)
			fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
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

int	find_cmd(t_data *data)
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
		data->cmd_flag = data->cmd_flag | FLAG_PATH_PERM;
	else
		data->cmd_flag = data->cmd_flag | FLAG_INV_CMD_FAIL;
	return (0);
}

void	parse_cmd(char *cmd, t_data *data)
{
	data->cmd.argv = ft_split(cmd, ' ');
	data->cmd.file = ft_strjoin("/", data->cmd.argv[0]);
	if (!data->cmd.argv || !data->cmd.file)
		ft_error("pipex", NULL, data, E_MALLOC_FAIL);
	find_cmd(data);
}

void	create_child(int flag, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork", NULL, data, E_FORK_FAIL);
	if (pid == 0)
	{
		if (data->cmd_flag & FLAG_PATH_PERM)
			ft_error("pipex", PATH_PERM_MSG, data, E_PATH_PERM);
		if (data->cmd_flag & FLAG_INV_CMD_FAIL)
			ft_error("pipex", INV_CMD_MSG, data, E_INV_CMD_FAIL);
		redirect_input(data, flag);
		redirect_output(data, flag);
		execve(data->cmd.path, data->cmd.argv, data->envp);
		ft_error("pipex", NULL, data, E_EXECVE_FAIL);
	}
}
