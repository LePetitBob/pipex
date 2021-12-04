/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/12/04 05:53:04 by vduriez          ###   ########.fr       */
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
	tmp = ft_split(cmd, ' ');
	dprintf(2, "eh\n");
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), tmp[0]);
		if (access(path, X_OK) == 0)
		{
			execve(path, tmp, envp);
			dprintf(2, "{%s}\n", path);
		}
		i++;
	}
}

void	child_process(char **av, int *i, int *fd, char **envp)
{
	int	fdin;
	printf("child %d\n", i[0]); 	//!   -------->REMOVE
	//if (i[0] == 0)
	//{
		fdin = open(av[1], O_RDONLY);
		close(fd[0]);
		dup2(fdin, 0);
		printf("exec child\n");
		dup2(fd[1], 1);
		ft_exec(av[2], envp);
	//}
	//else if (i[0] == i[1] - 2)
	//{
	//	close(fd[1]);
	//	dup2(fd[0], 0);
	//	dup2(open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777), 1);
	//	ft_exec(av[i[1] - 2], envp);
	//}
	//dup2(fd[0], 0);
	//dup2(fd[1], 1);
	//ft_exec(av[i[0] + 2], envp);
}

//void	parent_process(char **av, int ac, int *fd, char **envp)
//{
//	int		fdout;

//	fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
//	close(fd[1]);
//	dup2(fd[0], 0);
//	dup2(fdout, 1);
//	ft_exec(av[ac - 2], envp);
//}		//!  ft_exec("pwd", envp);

//int	main(int ac, char**av, char **envp)
//{
//	int		fd1[2];
//	//int		fd2[2];
//	pid_t	pid[ac - 3];
//	int		i[2];
//	int		ret;

//	//if (ac < 5)
//	//	return (0);
//	if (pipe(fd1) == -1)
//		exit(1);
//	i[0] = -1;
//	i[1] = ac;
//	while (++i[0] < ac - 3)
//	{
//		pid[i[0]] = fork();
//		if (pid[i[0]] < 0)
//			exit(1);
//		if (!pid[i[0]])
//			child_process(av, i, fd1, envp);
//	}
//	i[0] = -1;
//	while (++i[0] < ac - 4)
//		waitpid(pid[i[0]], &ret, 0);
//	return (0);
//}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		ret;
	int		i[2];
	int fdout;

	//if (ac < 5)
	//	return (0);
	
	if (pipe(fd) == -1)
		exit(1);
	i[0] = 0;
	i[1] = ac;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
		child_process(av, i, fd, envp);
	else
	{
		printf("parent (wait)\n");
		waitpid(pid, &ret, 0);
		printf("has waited\n");
		fdout = open(av[i[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], 0);
		dup2(fdout, 1);
		close(fd[0]);
		ft_exec(av[3], envp);
	}
}