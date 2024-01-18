/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:51 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/09 14:43:51 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "../includes/pipex.h"

void	redirect(int oldfd, int newfd, t_data *data)
{
	if (dup2(oldfd, newfd) == -1)
		error_exit("dup2", data);
	close(oldfd);
}

void	child(t_data *data, char **ep, int n)
{
	pid_t		pid;
	int			pipefd[2];
	static int	input_fd;

	if (input_fd == 0)
		input_fd = data->infile;
	if (pipe(pipefd) == -1)
		error_exit("pipe", data);
	pid = fork();
	if (pid == -1)
		error_exit("fork", data);
	if (pid == 0)
	{
		close(pipefd[0]);
		redirect(input_fd, STDIN_FILENO, data);
		redirect(pipefd[1], STDOUT_FILENO, data);
		//1:STDIN: infile STDOUT: pipefd[1]
		//2:STDIN: pipefd[0] STDOUT: pipefd[1]
		execve(data->cmd[n].path, data->cmd[n].argv, ep);
		error_exit("execve", data);
	}
	else
	{
		close(pipefd[1]);
		if (n == data->nb_cmd - 1)
			redirect(data->outfile, STDOUT_FILENO, data);
		else
			redirect(pipefd[0], input_fd, data);
		//input_fd: pipefd[0]
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;

	init_data(&data, av, ep, ac);
	if (ac != 5)
		error_exit("Wrong number of arguments", &data);// delete perror
	child(&data, ep, 0);
	child(&data, ep, 1);
	close(data.outfile);
	error_exit("OK", &data);
}
