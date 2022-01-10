/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/10 18:35:53 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

void	ft_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	tmp = ft_split(cmd, ' ');
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), tmp[0]);
		if (access(path, X_OK) == 0)
			execve(path, tmp, envp);
		free(path);
		i++;
	}
	ft_free(paths);
	ft_free(tmp);
	exit(1);
}

void	child_process(char **av, int i, int *fd, char **envp)
{
	int	fdi;

	if (i == 0)
	{
		fdi = open(av[1], O_RDONLY);
		if (fdi < 0 || check_infile(av[1]))
			exit(1);
		dup2(fdi, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(fdi);
		ft_exec(av[2], envp);
	}
	fdi = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdi < 0)
		exit(1);
	dup2(fd[0], 0);
	dup2(fdi, 1);
	close(fd[0]);
	close(fd[1]);
	close(fdi);
	ft_exec(av[3], envp);
}

int	check_infile(char *infile)
{
	int	in;

	in = open(infile, O_RDONLY);
	if (in < 0 && strcmp(errno, "EACCESS"))
	{
		write(2, "Infile does not exist or permission denied\n", 45);
		return (1);
	}
	return (0);
}

int	main(int ac, char**av, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		i;
	int		ret;

	if (ac != 5)
		return (1);
	i = -1;
	if (pipe(fd) == -1)
		exit(1);
	while (++i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		if (!pid[i])
			child_process(av, i, fd, envp);
	}
	close(fd[0]);
	close(fd[1]);
	i = -1;
	while (++i < 2)
		waitpid(pid[i], &ret, WUNTRACED);
	return (0);
}
