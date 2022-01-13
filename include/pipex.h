/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:52:11 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/13 17:15:48 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_exec
{
	char	**paths;
	char	**tmp;
	char	*path;
	char	*path2;
	int		i;
}				t_exec;

void	ft_putstr(char *s);
void	ft_exit(int error, char *cmd);
void	close_pipe(int fd[2]);
void	ft_close_all(int fd[4]);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		*init_i(int i[3], int ac);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *str, char c);

#endif