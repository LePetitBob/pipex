/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/11/29 10:29:15 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(void)
{
	exit(1);
}

void	child_process(void)
{
}

void	parent_process(void)
{
}

int	main(int ac, char**av, char **envp)
{
	int		fd[2];
	int		pid;
	char	**paths;
	char	**argv;
	char	*path;
	int		i = 0;
	//if (ac != 5)
	//	return (0);
	//if (pipe(fd) == -1)
	//	exit(1);
	//pid = fork();
	//if (pid < 0)
	//	exit(1);
	//if (!pid)
	//{
	//	child_process();
	//}
	//else
	//{
	//	waitpid(-1, NULL, 0);
	//	parent_process();
	//}
	while(!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), av[1]);
		if (access(path, X_OK) == 0)
			printf("%s\n", path);
			//return (path);
		//argv = ft_split(av, ' ');
		execve(path, (const char *) av[2], envp);
		i++;
	}
}

