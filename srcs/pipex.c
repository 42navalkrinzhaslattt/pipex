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



void	ft_error(char *cmd, char *msg, t_data *data, int flag)
{
	if (!msg)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(msg, 2);
	}
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data, char **av, char **ep, int ac)
{
	data->paths = NULL;
	data->outfile = av[ac - 1];
	data->infile = av[1];
	data->envp = ep;
	data->prev_fd_in = -1;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	if (!data->paths)
		ft_error("pipex", NULL, data, E_MALLOC);
}
void	create_child(char *cmd, int flag, t_data *data)
{

}


void	run_pipeline(char **av, t_data *data)
{
	if (pipe(data->pipefd) == -1)
		ft_error("pipex", NULL, &data, E_PIPE);
	create_child(av[2], FD_FILE_IN, data);
	create_child(av[3], FD_PIPE_IN | FD_FILE_OUT | ST_SAVE , data);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;
	pid_t	pid;
	int		status;

	if (ac != 5)
		ft_error("pipex", INV_ARGC_MSG, &data, E_INV_ARGC);
	init_data(&data, av, ep, ac);
	run_pipeline(av, &data);
	pid = 1;
	while (pid > 0)
	{
		pid = wait(&data.last_status);
	}
	while (pid > 0)//can be replaced with while(wait(&data.status) > 0)
	{
		pid = wait(&status);
		if (pid == data.last_pid)
			data.last_status = status;
	}
	return (WEXITSTATUS(data.last_status));
}
