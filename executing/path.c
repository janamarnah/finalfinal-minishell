/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:29:41 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while ((s1[count] || s2[count]) && count < n)
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

static char	*findpathword(char **env, char *path_env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_env = env[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

static char	*joincommand(char *path, char *command)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, command);
	free(tmp);
	return (full);
}

static char	*searchpath(char **paths, char *cmd)
{
	char	*final_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		final_path = joincommand(paths[i], cmd);
		if (!final_path)
			return (NULL);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

char	*findpath(char **envp, char *command)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	path_env = NULL;
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = findpathword(envp, path_env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	cmd_path = searchpath(paths, command);
	free_tab(paths);
	return (cmd_path);
}
