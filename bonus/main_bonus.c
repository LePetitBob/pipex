/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/12/05 13:53:54 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	while(!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	tmp = ft_split(cmd, ' ');
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), tmp[0]);
		if (access(path, X_OK) == 0)
		{
			execve(path, tmp, envp);
		}
		i++;
	}
}

void	child_process(char **av, int *i, int *fd, char **envp)
{
	int	fdi;

	if (i[0] == 0)
	{
		fdi = open(av[1], O_RDONLY);
		dup2(fdi, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(fdi);
		ft_exec(av[2], envp);
	}
	else if (i[0] == i[1] - 4)
	{
		fdi = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], 0);
		dup2(fdi, 1);
		close(fd[0]);
		close(fd[1]);
		close(fdi);
		ft_exec(av[i[1] - 2], envp);
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	ft_exec(av[i[0] + 2], envp);
}

int	main(int ac, char**av, char **envp)
{
	//int		fd[2][2];
	int		fd[2];
	pid_t	pid[ac - 3];
	int		i[2];
	int		ret;

	if (ac < 5)
		return (0);
	if (pipe(fd) == -1)
		exit(1);
	//if (pipe(fd[0]) == -1) //!
	//	exit(1);
	//if (pipe(fd[1]) == -1)
	//	exit(1);			 //!
	i[0] = -1;
	i[1] = ac;
	while (++i[0] < ac - 3)
	{
		pid[i[0]] = fork();
		if (pid[i[0]] < 0)
			exit(1);
		if (!pid[i[0]])
			child_process(av, i, fd, envp);
			//child_process(av, i, fd[0], envp); //!
	}
	close(fd[0]);
	close(fd[1]);
	//close(fd[0][0]); //!
	//close(fd[0][1]);
	//close(fd[1][0]);
	//close(fd[1][1]); //!
	i[0] = -1;
	while (++i[0] < ac - 3)
		waitpid(pid[i[0]], &ret, 0);
	return (0);
}
