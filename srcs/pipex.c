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

#include "pipex.h"
//#include "../includes/pipex.h"

void	child1(t_data *data, char **ep)
{
	close(data->pipefd[1]);
	if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2", data);
	close(data->pipefd[0]);
	close(data->input_fd);
	execve(data->cmd[0].path, data->cmd[0].argv, ep);
}

void	child2()
{

}

int	main(int ac, char **av, char **ep)
{
	t_data	data;
//	char	buf;

	if (ac != 5)
		error_exit("Wrong number of arguments", &data);
	init_data(&data, av, ep, ac);
	if (pipe(data.pipefd) == -1)
		error_exit("pipe", &data);
	data.pid[0] = fork();
	if (data.pid[0] == -1)
		error_exit("fork", &data);
	if (data.pid == 0)
		child1(&data, ep);
	data.pid[1] = fork();
	if (data.pid[1] == -1)
		error_exit("fork", &data);
	if (data.pid[1] == 0)
		//child2(&data, ep);
	close(data.pipefd[0]);
//	while (read(data.input_fd, &buf, 1) > 0)
//		write(data.pipefd[1], &buf, 1);
	close(data.pipefd[1]);
	close(data.input_fd);
	waitpid(data.pid[0], NULL, 0);
	waitpid(data.pid[1], NULL, 0);
	error_exit("OK", &data);
}
