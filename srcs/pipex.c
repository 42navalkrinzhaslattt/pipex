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
//	waitpid(-1, &data.status, 0);
	error_exit("OK", &data);
}
