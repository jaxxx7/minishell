/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanisubu <yanisubu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by yanisubu          #+#    #+#             */
/*   Updated: 2026/01/15 10:00:00 by yanisubu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(char *name, char **env)
{
	int		i;
	size_t	len;

	if (!name || !env)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_val(char *name, char **env)
{
	int	index;

	index = get_env_index(name, env);
	if (index == -1)
		return (NULL);
	return (ft_strchr(env[index], '=') + 1);
}

int	set_env_var(char *name, char *value, char ***env)
{
	int		index;
	char	*new_var;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (-1);
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_var)
		return (-1);
	index = get_env_index(name, *env);
	if (index >= 0)
	{
		free((*env)[index]);
		(*env)[index] = new_var;
		return (0);
	}
	return (add_env_var(new_var, env));
}

int	add_env_var(char *new_var, char ***env)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (-1);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	unset_env_var(char *name, char ***env)
{
	int	index;
	int	i;

	index = get_env_index(name, *env);
	if (index == -1)
		return (0);
	free((*env)[index]);
	i = index;
	while ((*env)[i + 1])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}
