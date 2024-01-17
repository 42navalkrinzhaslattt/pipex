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

void	init_data(t_data *data, char **av, char **ep, int ac)
{
	int	i;

	data->input_fd = open(av[1], O_RDONLY);
	data->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->input_fd == -1 || data->output_fd == -1)
		error_exit("file", data);
	data->nb_cmd = ac - 3;
	data->cmd = ft_calloc(data->nb_cmd, sizeof(t_cmd));
	data->pid = ft_calloc(data->nb_cmd, sizeof(pid_t));
	data->paths = NULL;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	i = -1;
	while (++i < ac - 3)
		parse_cmd(av[i + 2], data, i);
	if (!data->paths || !data->cmd || data->pid)
		error_exit("malloc", data);
}
