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
#include "../includes/pipex.h"


void	child(t_data *data)
{

}

int	main(int ac, char **av, char **ep)
{
	t_data	data;

	if (ac != 5)
		error_exit("Wrong number of arguments\n", &data);
	init_data(&data, av, ep, ac);
	if (pipe(data.pipefd) == -1)
		error_exit("pipe", &data);
	data.pid = fork();
	if (data.pid == -1)
		error_exit("fork", &data);
	if (data.pid == 0)
		child(&data);
	error_exit("OK\n", &data);
}
