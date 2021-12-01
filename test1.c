/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:39:26 by vduriez           #+#    #+#             */
/*   Updated: 2021/11/30 19:01:56 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(void)
{
	int		pipefd[2];
	int		fd_in;
	pid_t	pid;
	int		count;
	int		i;

	i = 0;
	count = 3;
	fd_in = dup(STDIN_FILENO);  // sauvegarde du stin dans fd_in.
	while (i < count) // tant qu'il y a des pipes.
	{
		pipe(pipefd);
		pid = fork(); // duplication du processus
		if (pid == 0) // pid enfant;
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != count)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			close(fd_in);
			exit(0); // sortie du programme enfant;
		}
		// pid parent;
		dup2(pipefd[0], fd_in); // sauvegarde du  fd_pipe[0] dans fd_in;
		close(pipefd[0]); // fermeture dans le pipe parent du pipefd[0];
		close(pipefd[1]); // fermeture dans le pipe parent du pipefd[1];
		i++;
	}
	close(fd_in);
	i = -1;
	while (++i < count)
		wait(NULL);
	return (0);
}
