/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/12/01 03:01:38 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(path, X_OK) == 0)
		{
			//printf("-->%s\n", path);		//! REMOVE
			tmp = ft_split(cmd, ' ');
			execve(path, tmp, envp);
			return ;
		}
		i++;
	}
}

void	child_process(char **av, int *fd, char **envp)
{
	int	fdout;

	dup2(fd[1], 1);
	dup2(fdout, 0);
	close(fd[0]);
	ft_exec(av[3], envp);
	//close(fd[1]);
	//write(fd[1], cmd, ft_strlen(cmd));
}

void	parent_process(char **av, int *fd, char **envp)
{
	//char	*str;
	int		fdin;

	fdin = open(av[4], O_WRONLY | O_CREAT, 0777);
	//str = malloc(250);
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(fdin, 1);
	//read(fd[0], str, 250);
	//printf("{%s}\n", str);
	ft_exec(av[3], envp);
	//close(fd[0]);
}		//!  ft_exec("pwd", envp);

int	main(int ac, char**av, char **envp)
{
	int		fd[2];
	int		pid;
	char	*str;

	ft_exec("ls", envp);
	if (ac != 5)
		return (0);
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
		child_process(av, fd, envp);
	else
	{
		waitpid(-1, NULL, 0);
		parent_process(av, fd, envp);
	}
}

