/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by nam-vu            #+#    #+#             */
/*   Updated: 2024/02/15 23:18:11 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_data(t_data *data, char **av, char **ep, int ac)
{
	data->paths = NULL;
	data->outfile = av[ac - 1];
	data->infile = av[1];
	data->envp = ep;
	data->prev_fd_in = -1;
	data->cmd_flag = 0;
	data->cmd.file = NULL;
	data->cmd.argv = NULL;
	data->cmd.path = NULL;
	data->heredoc = 0;
	if (!ft_strncmp(av[1], "here_doc", 9) && ac >= 6)
		data->heredoc = 1;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	if (!data->paths)
		ft_error("pipex", NULL, data, E_MALLOC_FAIL);
}

static void	run_piped_proccess(int in_flag, t_data *data)
{
	if (pipe(data->pipefd))
		ft_error("pipex", NULL, data, E_PIPE_FAIL);
	create_child(in_flag | FD_PIPE_OUT, data);
	data->prev_fd_in = dup(data->pipefd[0]);
	if (data->prev_fd_in < 0)
		ft_error("pipex", NULL, data, E_DUP_FAIL);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

static void	run_pipeline(int ac, char **av, t_data *data)
{
	int	i;

	if (data->heredoc)
		heredoc(av[2], data);
	else
	{
		parse_cmd(av[2], data);
		run_piped_proccess(FD_FILE_IN, data);
		free_cmd(&data->cmd);
	}
	i = 2;
	while (++i < ac - 2)
	{
		parse_cmd(av[i], data);
		run_piped_proccess(FD_PREV_IN, data);
		free_cmd(&data->cmd);
	}
	parse_cmd(av[ac - 2], data);
	create_child(FD_PREV_IN | FD_FILE_OUT, data);
	free_cmd(&data->cmd);
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
<<<<<<< HEAD
			ft_putstr_fd(msg, 2);
=======
		{
			ft_putstr_fd(msg, 2);
			if (flag == E_INV_CMD_FAIL || flag == E_EMPTY_CMD
				|| flag == E_PATH_PERM)
			{
				ft_putstr_fd(data->cmd.file + 1, 2);
				ft_putstr_fd("\n", 2);
			}
		}
>>>>>>> e6eb84a (heredoc fixed)
	}
	free_arr((void **)data->paths);
	free_cmd(&data->cmd);
	exit(flag);
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;
	int		status;

	if (ac < 5)
	{
		write(2, "pipex: ", 7);
		write(2, INV_ARGC_MSG, 26);
		exit(E_INV_ARGC);
	}
	init_data(&data, av, ep, ac);
	run_pipeline(ac, av, &data);
	while (wait(&status) > 0)
	{
	}
	free_arr((void **)data.paths);
	return (WEXITSTATUS(status));
}
