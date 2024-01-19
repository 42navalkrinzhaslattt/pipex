/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:25 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/09 17:13:25 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../includes/pipex.h"

int	find_cmd(t_data *data, int n)
{
	char	*temp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		temp = ft_strjoin(data->paths[i], data->cmd[n].name);
		if (!temp)
			error_exit("malloc", data);
		if (!access(temp, X_OK))
		{
			data->cmd[n].path = temp;
			return (1);
		}
		free(temp);
	}
	data->cmd[n].path = NULL;
	return (0);
}

void	parse_cmd(char *cmd, t_data *data, int n)
{
	int	i;

	i = 0;
	while (cmd[i] != ' ' && cmd[i] != 0)
		i++;
	data->cmd[n].name = ft_calloc(i + 2, sizeof(*cmd));
	if (!data->cmd[n].name)
		error_exit("malloc", data);
	data->cmd[n].name[0] = '/';
	ft_strlcpy(data->cmd[n].name + 1, cmd, i + 1);
	data->cmd[n].argv = ft_split(cmd, ' ');
	if (!data->cmd[n].argv)
		error_exit("malloc", data);
	if (!find_cmd(data, n))
		error_exit("malloc", data);
}

void	assign_data(t_data *data, char **av, char **ep, int ac)
{
	int	i;

	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->infile == -1 || data->outfile == -1)
		error_exit("open", data);
	data->cmd = ft_calloc(data->nb_cmd, sizeof(t_cmd));
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	i = -1;
	while (++i < ac - 3)
		parse_cmd(av[i + 2], data, i);
	data->pipefd = ft_calloc((data->nb_cmd - 1) * 2, sizeof(int));
	if (!data->paths || !data->cmd || !data->pipefd)
		error_exit("malloc", data);
	while (--ac - 4 >= 0)
		if (pipe(data->pipefd + 2 * ac - 8) == -1)
			error_exit("pipe", data);
}

void	init_data(t_data *data, char **av, char **ep, int ac)
{
	data->cmd = NULL;
	data->paths = NULL;
	data->nb_cmd = ac - 3;
	data->pipefd = NULL;
	data->outfile = -1;
	data->infile = -1;
	assign_data(data, av, ep, ac);
}