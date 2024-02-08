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

#include "pipex.h"

static void	init_data(t_data *data, char **av, char **ep, int ac)
{
	data->paths = NULL;
	data->outfile = av[ac - 1];
	data->infile = av[1];
	data->envp = ep;
	data->prev_fd_in = -1;
	data->cmd.file = NULL;
	data->cmd.argv = NULL;
	data->cmd.path = NULL;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	if (!data->paths)
		ft_error("pipex", NULL, data, E_MALLOC_FAIL);
}

static void	run_pipeline(char **av, t_data *data)
{
	if (pipe(data->pipefd) == -1)
		ft_error("pipex", NULL, data, E_PIPE_FAIL);
	create_child(av[2], FD_FILE_IN | FD_PIPE_OUT, data);
	create_child(av[3], FD_PIPE_IN | FD_FILE_OUT | ST_SAVE, data);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	ft_error(char *cmd, char *msg, t_data *data, int flag)
{
	if (!msg)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (flag == E_OPEN_FAIL)
			perror(msg);
		else
			ft_putstr_fd(msg, 2);
	}
	free_arr((void **)data->paths);
	free_cmd(&data->cmd);
	exit(flag);
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;
	int		status;

	if (ac != 5)
	{
		write(2, "pipex: ", 7);
		write(2, INV_ARGC_MSG, 26);
		exit(E_INV_ARGC);
	}
	init_data(&data, av, ep, ac);
	run_pipeline(av, &data);
	while (wait(&status) > 0)
	{
	}
	free_arr((void **)data.paths);
	return (WEXITSTATUS(status));
}
