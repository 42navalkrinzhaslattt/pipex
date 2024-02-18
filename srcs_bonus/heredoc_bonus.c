/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:59:14 by nam-vu            #+#    #+#             */
/*   Updated: 2024/02/17 00:59:14 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_child(t_data *data, char *limiter)
{
	char	*line;
<<<<<<< HEAD
	char	line_len;
=======
	size_t	line_len;
>>>>>>> e6eb84a (heredoc fixed)

	close(data->pipefd[0]);
	write(1, "heredoc> ", 10);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		line_len = ft_strlen(line);
		write(data->pipefd[1], line, line_len);
<<<<<<< HEAD
		if (!ft_strncmp(line, limiter, line_len - 1)
=======
		if (line_len == ft_strlen(limiter) + 1
			&& !ft_strncmp(line, limiter, line_len - 1)
>>>>>>> e6eb84a (heredoc fixed)
			&& !ft_strncmp(line + line_len - 1, "\n\0", 2))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		free(line);
		write(1, "heredoc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
	exit(EXIT_SUCCESS);
}

void	heredoc(char *limiter, t_data *data)
{
	pid_t	pid;

	if (pipe(data->pipefd))
		ft_error("pipex", NULL, data, E_PIPE_FAIL);
	pid = fork();
	if (pid < 0)
		ft_error("pipex", NULL, data, E_FORK_FAIL);
	if (pid == 0)
		heredoc_child(data, limiter);
	else
	{
		data->prev_fd_in = dup(data->pipefd[0]);
		if (data->prev_fd_in < 0)
			ft_error("pipex", NULL, data, E_DUP_FAIL);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		wait(NULL);
	}
}
