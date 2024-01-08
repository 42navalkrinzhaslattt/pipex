#include "pipex.h"
#include "../includes/pipex.h"

char	*read_file(char *file)
{
	char		*res;
	char		buf[BUFF_SIZE + 1];
	int			fd;
	ssize_t		nbytes;
	ssize_t		size;

	fd = open(file, O_RDONLY);
	size = 0;
	nbytes = read(fd, buf, BUFF_SIZE);
	while (nbytes > 0)
	{
		size += nbytes;
		nbytes = read(fd, buf, BUFF_SIZE);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	read(fd, res, size);
	res[size] = 0;
	close(fd);
	return (res);
}

void	error_exit(char *str, t_data *data)
{
	int	i;

	while (*str)
		write(2, str++, 1);
	if (data->input)
		free(data->input);
	if (data->cmd_name)
		free(data->cmd_name);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->cmd_argv)
	{
		i = -1;
		while (data->cmd_argv[++i])
			free(data->cmd_argv[++i]);
		free(data->cmd_argv);
	}
	if (data->paths)
	{
		i = -1;
		while (data->paths[++i])
			free(data->paths[++i]);
		free(data->paths);
	}
	exit(EXIT_FAILURE);
}

int		find_cmd(t_data *data)
{
	char	*temp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		temp = ft_strjoin(data->paths[i], data->cmd_name);
		if (!temp)
			error_exit("malloc error", data);
		if (!access(temp, X_OK))
		{
			data->cmd_path = temp;
			return (1);
		}
		free(temp);
	}
	data->cmd_path = NULL;
	return (0);
}

void	child(char *cmd, char **ep, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i] != ' ' && cmd[i] != 0)
		i++;
	data->cmd_name = ft_calloc(i + 1, sizeof(*cmd));
	if (!data->cmd_name)
		error_exit("malloc issue\n", data);
	data->cmd_name[0] = '/';
	ft_strlcpy(data->cmd_name + 1, cmd, i + 1);
	data->cmd_argv = ft_split(cmd + i + 1, ' ');// add infile as an argument somehow
	if (!data->cmd_argv)
		error_exit("malloc issue\n", data);
	if (!find_cmd(data))
		error_exit("command not found\n", data);
	execve(data->cmd_path, data->cmd_argv, ep);
}

void	init_data(t_data *data, char **ep)
{
	data->input = NULL;
	data->cmd_name = NULL;
	data->cmd_argv = NULL;
	data->cmd_path = NULL;
	data->paths = NULL;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			data->paths = ft_split(*ep + 5, ':');
		ep++;
	}
	if (!data->paths)
		error_exit("Error while parsing PATH\n", data);
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;

	if (ac != 5)
		error_exit("Wrong number of arguments\n", &data);
	init_data(&data, ep);
	data.input = read_file(av[1]);//no need to pares input
	if (!data.input)
		error_exit("No such file or directory\n", &data);
	data.pid = fork();
	if (data.pid == 0)
		child(av[2], ep, &data);
	wait(NULL);
//	data.pid = fork();
//	if (data.pid == 0)
//		child(av[3], ep, &data);
//	wait(NULL);
	printf("back to father proccess\n");
	error_exit("OK\n", &data);
}
