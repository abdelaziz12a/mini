/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:38:30 by aaboudra          #+#    #+#             */
/*   Updated: 2025/07/11 12:35:00 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_shell_level(t_cmd *cmd)
{
	char	new_level[20];
	char	*shell_level;

	if (cmd->args && cmd->args[0] && is_minishell_command(cmd->args[0]))
	{
		shell_level = getenv("SHLVL");
		if (shell_level)
		{
			snprintf(new_level, sizeof(new_level), "%d",
				ft_atoi(shell_level) + 1);
			setenv("SHLVL", new_level, 1);
		}
	}
}

void	execute_command_in_child(t_cmd *cmd, t_data *data)
{
	char	*executable_path;

	setup_shell_level(cmd);
	signal_init();
	if (handle_child_redirections(cmd) != 0)
		exit(EXIT_GENERAL_ERROR);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		exit(execute_builtin_child(cmd, data));
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	executable_path = find_executable_path(cmd->args[0], data->tenv, data);
	if (!executable_path)
		handle_no_executable(cmd, data);
	execute_with_path(cmd, data, executable_path);
}
