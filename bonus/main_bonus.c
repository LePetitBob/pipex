/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/13 17:13:47 by vduriez          ###   ########.fr       */
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
	free(s);
}

void	ft_exec(char *cmd, char **envp)
{
	t_exec	exec;

	exec.i = 0;
	while (ft_strncmp(envp[exec.i], "PATH=", 5) != 0)
		exec.i++;
	if (!envp[exec.i])
		ft_exit(127, cmd);
	exec.tmp = ft_split(cmd, ' ');
	if (access(cmd, X_OK) == 0)
		execve(cmd, exec.tmp, envp);
	exec.paths = ft_split(envp[exec.i] + 5, ':');
	exec.i = 0;
	while (exec.paths[exec.i])
	{
		exec.path = ft_strjoin(exec.paths[exec.i], "/");
		exec.path2 = ft_strjoin(exec.path, exec.tmp[0]);
		if (access(exec.path2, X_OK) == 0)
			execve(exec.path2, exec.tmp, envp);
		exec.i++;
		free(exec.path);
		free(exec.path2);
	}
	ft_free(exec.tmp);
	ft_free(exec.paths);
	ft_exit(127, cmd);
}

void	ft_dup2(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}

void	child_process(char **av, int *i, int *fd, char **envp)
{
	int	fdi;

	if (i[0] == 0)
	{
		fdi = open(av[1], O_RDONLY);
		if (fdi < 0)
			ft_exit(126, av[1]);
		ft_dup2(fdi, fd[1]);
		close(fdi);
	}
	else if (i[0] == i[1] - 4)
	{
		fdi = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdi < 0)
			ft_exit(126, av[i[1] - 1]);
		ft_dup2(fd[2], fdi);
		close(fdi);
	}
	else
		ft_dup2(fd[2], fd[1]);
	ft_close_all(fd);
	ft_exec(av[i[0] + 2], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid[4096];
	int		i[3];
	int		fd[3];

	if (ac < 5)
		ft_exit(65, NULL);
	i[0] = -1;
	i[1] = ac;
	fd[2] = dup(STDIN_FILENO);
	while (++i[0] < ac - 3)
	{
		if (pipe(fd) < 0)
			ft_exit(127, "pipe");
		pid[i[0]] = fork();
		if (pid[i[0]] < 0)
			ft_exit(127, "fork");
		if (!pid[i[0]])
			child_process(av, i, fd, envp);
		close_pipe(fd);
	}
	close(fd[2]);
	i[0] = -1;
	while (++i[0] < ac - 3)
		waitpid(pid[i[0]], &i[2], 0);
	return (0);
}
