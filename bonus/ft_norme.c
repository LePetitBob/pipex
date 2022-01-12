/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 00:53:24 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/11 22:34:44 by vduriez          ###   ########.fr       */
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
