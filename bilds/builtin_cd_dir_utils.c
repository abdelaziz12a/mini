/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_dir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:15:00 by elben-id          #+#    #+#             */
/*   Updated: 2025/07/09 19:45:03 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_parent_dir(char *pwd_value, t_data *data)
{
	int		i;
	char	*parent_dir;

	i = ft_strlen(pwd_value) - 1;
	while (i >= 0 && pwd_value[i] != '/')
		i--;
	if (i > 0)
		parent_dir = ft_strndup(pwd_value, i, data);
	else if (i == 0)
		parent_dir = ft_strdup("/", data);
	else
		parent_dir = NULL;
	return (parent_dir);
}

int	handle_parent_dir(char *pwd_value, t_env **env_list,
		char *old_pwd_buffer, t_data *data)
{
	char	*parent_dir;

	parent_dir = extract_parent_dir(pwd_value, data);
	if (parent_dir && chdir(parent_dir) == 0)
	{
		if (old_pwd_buffer[0] != '\0')
			set_env_var(env_list, "OLDPWD", old_pwd_buffer, data);
		else
			set_env_var(env_list, "OLDPWD", pwd_value, data);
		set_env_var(env_list, "PWD", parent_dir, data);
		gc_free_ptr(parent_dir, data);
		gc_free_ptr(pwd_value, data);
		return (0);
	}
	if (parent_dir)
		gc_free_ptr(parent_dir, data);
	return (1);
}
