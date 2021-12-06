void	children(t_list *lexer, int fd_in)
{
	int		i;
	int		pipes[2];
	pid_t	pid;

	i = 0;
	while (i < (count_pipes(lexer) + 1))
	{
		pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != (count_pipes(lexer) + 1))
				dup2(pipes[1], STDOUT_FILENO);
			close_write_read(pipes);
			close(fd_in);
			if (!redirection(lexer, i, &g_ms.cpenv))
				exec_cmd(lexer, i, &g_ms.cpenv);
			exit(0);
		}
		dup2(pipes[0], fd_in);
		close_write_read(pipes);
		i++;
	}