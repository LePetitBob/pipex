/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/12/16 17:04:48 by vduriez          ###   ########.fr       */
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
			exit(1);
		}
		i++;
	}
	exit(1);
}

void	child_process(char **av, int *i, int *fd, char **envp)
{
	int 	k = 0;
	int	fdi;

	if (i[0] == 0)
	{
		fdi = open(av[1], O_RDONLY);
		dup2(fdi, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fdi);
	}
	else if (i[0] == i[1] - 4)
	{
		fdi = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd[0], STDIN_FILENO);
		dup2(fdi, STDOUT_FILENO);
		close(fdi);
	}
	else
	{
		dup2(fdi, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
		//close(fd[0]);
		//close(fd[1]);
		//close(fdi);
	ft_exec(av[i[0] + 2], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid[2];
	int		i[2];
	int		ret[ac - 3];
	int		fd[2 * (ac - 4)];

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int 	k = 0;
	int	fdi;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (ac < 5)
		return (1);
	i[0] = 0;
	i[1] = ac;
	//init();
	//while (i[0] < ac - 4)
	//{
	//	if (pipe(fd + 2 * i[0]) < 0)
	//		exit(1);
	//	i[0] += 2;
	//}

	i[0] = -1;
	while (++i[0] < ac - 3)
	{
		if (i[0] < ac - 4)
		{
			if (pipe(fd) < 0)
				exit(1);
		}
		pid[i[0]] = fork();		
		if (pid[i[0]] < 0)
			exit(1);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (!pid[i[0]])
		{
			if (i[0] == 0)
			{
				fdi = open(av[1], O_RDONLY);
				dup2(fdi, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fdi);
			}
			else if (i[0] == i[1] - 4)
			{
				fdi = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd[0], STDIN_FILENO);
				dup2(fdi, STDOUT_FILENO);
				close(fdi);
			}
			else
			{
				dup2(fdi, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (i[0])
				close(fdi);
			fdi = fd[0];
		}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//if (!pid[i[0]])
			//child_process(av, i, fd, envp);
		//close(fd[0]);
		//close(fd[1]);
	}
	i[0] = -1;
	while (++i[0] < ac - 4)
		close(fd[i[0]]);
	//close(fd[0]);
	//close(fd[1]);
	i[0] = -1;
	while (++i[0] < ac - 3)
		waitpid(pid[i[0]], &ret[i[0]], 0);
	return (0);
}
