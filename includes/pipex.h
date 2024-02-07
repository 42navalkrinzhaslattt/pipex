/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:33:15 by nam-vu            #+#    #+#             */
/*   Updated: 2024/01/27 21:33:15 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define BUFF_SIZE 1024

# define INV_ARGC_MSG "wrong number of arguments\n"
# define EMPTY_CMD_MSG "empty command\n"
# define INV_CMD_MSG "command not found\n"
# define PATH_PERM_MSG "Permission denied\n"

# define E_INV_ARGC 1
# define E_MALLOC_FAIL 2
# define E_PIPE_FAIL 3
# define E_FORK_FAIL 4
# define E_EMPTY_CMD 5
# define E_OPEN_FAIL 6
# define E_DUP2_FAIL 7
# define E_INV_CMD_FAIL 8
# define E_PATH_PERM 9
# define E_EXECVE_FAIL 10

# define FD_FILE_IN 1
# define FD_PIPE_IN 2
# define FD_PREV_IN 4
# define FD_FILE_OUT 8
# define FD_PIPE_OUT 16
# define ST_SAVE 32


# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*file;
	char	**argv;
	char	*path;
}	t_cmd;

typedef struct s_data
{
	int		pipefd[2];
	char	*infile;
	char	*outfile;
	char	**paths;
	char	**envp;
	int		prev_fd_in;
	t_cmd	cmd;
}	t_data;

//child.c
void	create_child(char *cmd, int flag, t_data *data);

//ft_split.c
char	**ft_split(char const *s, char c);

//pipex.c
void	ft_error(char *cmd, char *msg, t_data *data, int flag);
int	main(int ac, char **av, char **ep);

//utils.c
void	free_arr(void	**arr);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);

//utils2.c
void	ft_putstr_fd(char *s, int fd);
void	free_cmd(t_cmd *cmd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif