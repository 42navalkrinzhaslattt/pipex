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

typedef struct s_cmd
{
	char	*name;
	char	**argv;
	char	*path;
}	t_cmd;

typedef struct s_data
{
	pid_t	pid;
	int		pipefd[2];
	int		input_fd;
	int		output_fd;
	char	**paths;
	t_cmd	*cmd;
	int		nb_cmd;
}	t_data;

//pipex.c
int		main(int ac, char **av, char **ep);

//exit.c
void	free_cmd(t_cmd cmd);
void	error_exit(char *str, t_data *data);

//parse.c
int		find_cmd(t_data *data, int n);
void	parse_cmd(char *cmd, t_data *data, int n);
void	init_data(t_data *data, char **av, char **ep, int ac);

#endif