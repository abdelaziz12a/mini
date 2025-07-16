/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:05:00 by elben-id          #+#    #+#             */
/*   Updated: 2025/07/09 19:05:32 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_signals_and_close(int fd, void (*old_sigint)(int),
		void (*old_sigquit)(int))
{
	close(fd);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
}

int	setup_heredoc_fork(int *fd, char **file_name, t_data *data,
		void (**old_handlers)(int))
{
	*fd = open_file(file_name, data);
	old_handlers[0] = signal(SIGINT, SIG_IGN);
	old_handlers[1] = signal(SIGQUIT, SIG_IGN);
	return (fork());
}

int	handle_heredoc_parent(pid_t pid, char *file_name, t_cmd *cmd,
		void (**old_handlers)(int))
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, old_handlers[0]);
	signal(SIGQUIT, old_handlers[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(file_name);
		return (1);
	}
	cmd->in_file = file_name;
	return (0);
}
