/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:24:39 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	updateenv(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	char	*updatedvalue;

	if (!env || !key || key[0] == '\0')
		return (1);
	node = findenv(*env, key);
	if (node)
	{
		updatedvalue = ft_strdup(value);
		if (!updatedvalue)
			return (1);
		free(node->value);
		node->value = updatedvalue;
		return (0);
	}
	node = newenv(key, value);
	if (!node)
		return (1);
	addnode(env, node);
	return (0);
}

static char	*getpath(char **args, t_env **env, int fd)
{
	t_env	*home;

	if (args[1] && args[2])
	{
		errormsg("cd", "too many arguments", fd);
		return (NULL);
	}
	if (args[1])
		return (args[1]);
	home = findenv(*env, "HOME");
	if (!home || !home->value)
	{
		errormsg("cd", "HOME not set", fd);
		return (NULL);
	}
	return (home->value);
}

int	builtincd(char **args, t_env **env, int fd)
{
	char	oldpwd[MAXPATH];
	char	currentpwd[MAXPATH];
	char	*path;

	path = getpath(args, env, fd);
	if (!path)
		return (1);
	if (!getcwd(oldpwd, MAXPATH))
		return (errormsg("cd", "No such file or directory", fd), 1);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), 1);
	if (!getcwd(currentpwd, MAXPATH))
		return (errormsg("cd", "No such file or directory", fd), 1);
	if (updateenv(env, "OLDPWD", oldpwd))
		return (1);
	if (updateenv(env, "PWD", currentpwd))
		return (1);
	return (0);
}
