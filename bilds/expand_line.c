/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:16:50 by aaboudra          #+#    #+#             */
/*   Updated: 2025/07/13 19:36:30 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	expand_var_at(t_expand *exp)
{
	char	var_name[256];
	char	*value;

	get_var_name(exp->line, &exp->i, var_name);
	value = get_env_value(exp->data->tenv, var_name, exp->data);
	if (value)
	{
		ft_memcpy(exp->result + exp->j, value, ft_strlen(value));
		return (exp->j + ft_strlen(value));
	}
	return (exp->j);
}

int	is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*expand_line(const char *line, t_cmd *cmd, t_data *data)
{
	t_expand	exp;

	if (cmd->q_limeter)
		return (ft_strdup(line, data));
	exp.line = line;
	exp.data = data;
	exp.result = gc_malloc(calc_var_len(line, &exp.i, data) * 2 + 1, data);
	if (!exp.result)
		return (NULL);
	exp.i = 0;
	exp.j = 0;
	while (exp.line[exp.i])
	{
		if (exp.line[exp.i] == '$' && is_var_start(exp.line[exp.i + 1]))
			exp.j = expand_var_at(&exp);
		else
			exp.result[exp.j++] = exp.line[exp.i++];
	}
	exp.result[exp.j] = '\0';
	return (exp.result);
}
