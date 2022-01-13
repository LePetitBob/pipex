/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/13 20:48:47 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_exit(int error, char *cmd)
{
	if (error == 65)
	{
		write(2, "Expected format :\n./pipex Infile cmd1 cmd2 Outfile\n", 52);
		exit(65);
	}
	else if (error == 126)
	{
		ft_putstr(cmd);
		write(2, " : Permission denied or file doesn't exist\n", 44);
		exit(127);
	}
	else if (error == 127)
	{
		ft_putstr(cmd);
		write(2, " : Invalid command\n", 20);
		exit(127);
	}
}

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

void	child_process(char **av, int i, int *fd, char **envp)
{
	int	fdi;

	if (i == 0)
	{
		fdi = open(av[1], O_RDONLY);
		if (fdi < 0)
			ft_exit(126, av[1]);
		dup2(fdi, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(fdi);
		if (envp)
			ft_exec(av[2], envp);
	}
	fdi = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdi < 0)
		ft_exit(126, av[4]);
	dup2(fd[0], 0);
	dup2(fdi, 1);
	close(fd[0]);
	close(fd[1]);
	close(fdi);
	if (envp)
		ft_exec(av[3], envp);
}

int	main(int ac, char**av, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		i;
	int		ret;

	if (ac != 5)
		ft_exit(65, NULL);
	i = -1;
	if (pipe(fd) == -1)
		ft_exit(127, "pipe");
	while (++i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			ft_exit(127, "fork");
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
