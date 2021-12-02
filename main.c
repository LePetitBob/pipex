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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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
			return ;
		}
		i++;
	}
}

char	*get_first_cmd(char** av)
{
	char *cmd;

	cmd = malloc(ft_strlen(av[1]) + ft_strlen(av[2]) + 2);
	cmd = ft_strjoin(ft_strjoin(av[2], " "), av[1]);
	return (cmd);
}

void	child_process(char **av, int i, int *fd, char **envp)
{
	int		fdin;
	char	*firstcmd;

	dup2(fd[1], 1);
	dup2(fdin, 0);
	close(fd[0]);
	// if (i == 0 && ft_strcmp("cat", av[2]))
	// {
	// 	firstcmd = get_first_cmd(av);
	// 	ft_exec(firstcmd, envp);
	// }
	// else
		ft_exec(av[i + 2], envp);
}

void	parent_process(char **av, int ac, int *fd, char **envp)
{
	int		fdout;

	fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(fdout, 1);
	ft_exec(av[ac - 2], envp);
}		//!  ft_exec("pwd", envp);

int	main(int ac, char**av, char **envp)
{
	int		fd[2];
	pid_t	pid[ac - 3];
	char	*str;
	int		i;

	if (ac < 5)
		return (0);
	if (pipe(fd) == -1)
		exit(1);
	i = 0;
	while (i < ac - 3)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		if (!pid[i])
			child_process(av, i, fd, envp);
		i++;
	}
	i = 0;
	while (i < ac - 3)
	{
		waitpid(pid[i], NULL, 0);
		parent_process(av, ac, fd, envp);
	}
}

