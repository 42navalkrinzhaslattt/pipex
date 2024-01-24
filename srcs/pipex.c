/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:51 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/19 12:36:42 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "../includes/pipex.h"

void	redirect(int input_fd, int output_fd, t_data *data)
{
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
		error_exit("dup2", data);
	if (input_fd != 0)
		close(input_fd);
	if (output_fd != 1)
		close(output_fd);
}

void	close_pipes()
{

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
			redirect(data->pipefd[n * 2 - 2], data->pipefd[n * 2 + 1] , data);
		close_pipes();
		parse_cmd(cmd, data, n);//add error handling
		execve(data->cmd[n].path, data->cmd[n].argv, ep);
	}
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;

	init_data(&data, av, ep, ac);
	if (ac != 5)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(EXIT_FAILURE);
	}
	child(&data, av[2], 0, ep);
	child(&data, av[3], 1, ep);
	error_exit("OK", &data);
}
