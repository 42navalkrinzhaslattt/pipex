#ifndef PIPEX_H
# define PIPEX_H
# define BUFF_SIZE 1024
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_data
{
	pid_t	pid;
	int		pipefd[2];
	int		input_fd;
	char	*input;
	char	**paths;
	char	*cmd_name;
	char	**cmd_argv;
	char	*cmd_path;
}	t_data;

char	*read_file(char *file);
void	error_exit(char *str, t_data *data);
int		find_cmd(t_data *data);
void	child(char *cmd, char **ep, t_data *data);
void	init_data(t_data *data, char **ep);
int	main(int ac, char **av, char **ep);

#endif