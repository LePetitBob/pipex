/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:40 by vduriez           #+#    #+#             */
/*   Updated: 2021/11/26 17:54:13 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void	ft_exit(void)
{
	exit(EXIT_FAILURE);
}

void	child_process(void)
{
}

void	parent_process(void)
{
}

int	main(int ac, char**av, char **envp)
{
	int	fd[2];
	int	pid;

	if (ac != 5)
		return (0);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (!pid)
		child_process();
	else
	{
		parent_process();
	}
}
