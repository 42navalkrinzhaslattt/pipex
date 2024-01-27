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
	char	*name;
	char	**argv;
	char	*path;
}	t_cmd;

typedef struct s_data
{
	int		*pipefd;
	int		infile;
	int		outfile;
	char	**paths;
	t_cmd	*cmd;
	int		nb_cmd;
	int		status;
}	t_data;

//child.c
void	close_pipes(t_data *data, int n);
void	redirect(int input_fd, int output_fd, t_data *data);
void	child(t_data *data, char *cmd, int n, char **ep);

//exit.c
void	free_cmd(t_cmd *cmd);
void	error_exit(char *str, t_data *data);

//ft_split.c
int		is_sep(char c, char sep);
int		count_str(char const *str, char sep);
int		count_strlen(char const *str, char sep, int n);
char	*save_str(char const *str, char sep, int n);
char	**ft_split(char const *s, char c);

//pipex.c
int		main(int ac, char **av, char **ep);

//parse.c
int		find_cmd(t_data *data, int n);
void	parse_cmd(char *cmd, t_data *data, int n);
void	assign_data(t_data *data, char **av, char **ep, int ac);
void	init_data(t_data *data, char **av, char **ep, int ac);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif