/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 00:53:24 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/13 17:11:19 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	*init_i(int i[3], int ac)
{
	i[1] = ac;
	i[0] = -1;
	return (i);
}

void	close_pipe(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

void	ft_close_all(int fd[3])
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
}

void	ft_exit(int error, char *cmd)
{
	if (error == 65)
	{
		write(2, "Expected :\n./pipex_bonus Infile cmd1 ... cmdX outfile\n", 55);
		exit(65);
	}
	else if (error == 126)
	{
		ft_putstr(cmd);
		write(2, "Permission denied or file doesn't exist\n", 41);
		exit(127);
	}
	else if (error == 127)
	{
		ft_putstr(cmd);
		write(2, " : Invalid command\n", 20);
		exit(127);
	}
}
