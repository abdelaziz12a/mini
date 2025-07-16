/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by aaboudra          #+#    #+#             */
/*   Updated: 2025/07/13 01:19:53 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_redirection_filename(char *filename, t_data *data)
{
	char	*expanded;
	char	**words;
	int		word_count;

	expanded = expand_var(filename, data);
	if (!expanded || !*expanded)
		return (NULL);
	words = ft_split(expanded, ' ', data);
	word_count = 0;
	while (words && words[word_count])
		word_count++;
	if (word_count != 1)
		return (NULL);
	return (expanded);
}

static void	handle_redirection_error(t_cmd *cmd,
		t_comand *token, int redir_type)
{
	display_error_message("minishell", token->next->word,
		"ambiguous redirect");
	if (redir_type == T_REDIR_IN)
	{
		cmd->in_file = NULL;
		cmd->has_redirect_error = 1;
	}
	else
	{
		cmd->out_file = NULL;
		cmd->has_redirect_error = 1;
	}
}

void	handle_redirection(t_cmd *cmd, t_comand *token, t_data *data,
	int redir_type)
{
	char	*expanded_filename;

	expanded_filename = expand_redirection_filename(token->next->word, data);
	if (!expanded_filename)
		handle_redirection_error(cmd, token, redir_type);
	else
	{
		if (redir_type == T_REDIR_IN)
			cmd->in_file = expanded_filename;
		else
			cmd->out_file = expanded_filename;
	}
	if (redir_type == T_REDIR_IN)
		cmd->in_type = T_REDIR_IN;
	else
		cmd->out_type = redir_type;
}

t_cmd	*init_node(t_data *data)
{
	t_cmd	*node;

	node = gc_malloc(sizeof(t_cmd), data);
	node->args = NULL;
	node->in_file = NULL;
	node->out_file = NULL;
	node->in_type = 0;
	node->out_type = 0;
	node->next = NULL;
	node->argc = 0;
	node->q_limeter = 0;
	return (node);
}
